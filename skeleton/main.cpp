#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include "ParticleSystem.h"
#include "WorldManager.h"

#include <iostream>

using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

/// <summary>
/// Sistema de particulas
/// </summary>
std::unique_ptr<ParticleSystem> particleSystem;

/// <summary>
/// World Manager
/// </summary>
std::unique_ptr<WorldManager> worldManager;

// Fin del juego --> no se actua frente a colisiones
bool endGame = false;


// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	// Sistema de particulas
	particleSystem = std::make_unique<ParticleSystem>();

	// World Manager
	worldManager = std::make_unique<WorldManager>(gScene, gPhysics);
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);

	// Actualiza el sistema de particulas
	particleSystem->update(t);

	// Actualiza la escena
	worldManager->update(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	case ' ':
		worldManager->addForce(GetCamera()->getDir() * 500);
		break;
	case 'L':
		//particleSystem->shootFirework(0);
		/*cout << GetCamera()->getEye().x;
		cout << GetCamera()->getEye().y;
		cout << GetCamera()->getEye().z;
		cout << GetCamera()->getDir().x;
		cout << GetCamera()->getDir().y;
		cout << GetCamera()->getDir().z;*/
		break;
	case 'R':
		worldManager->setBallStart();
		break;
	case '1':
		worldManager->createWorldScene();
		break;
	case 'F': 
		//GetCamera()->changeFollow(worldManager->getFollowActor());
		break;
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	/*PX_UNUSED(actor1);
	PX_UNUSED(actor2);*/

	if (endGame) return;

	if (actor1->getName() == "ball" && actor2->getName() == "goal")
	{
		if (!worldManager->getLastScene()) worldManager->changeSceneActive();
		else 
		{ 
			particleSystem->generateFirework(); 
			particleSystem->shootFirework(0);
			endGame = !endGame;
		}

	}

	else if (actor1->getName() == "ball" && actor2->getName() == "bomb") 
	{
		worldManager->generateExplosion(actor2);
	}
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}