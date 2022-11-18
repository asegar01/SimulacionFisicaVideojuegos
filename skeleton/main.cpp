#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include "Particle.h"
#include "Projectile.h"
#include "ParticleSystem.h"

#include <iostream>

#include <list>
#include <chrono>

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
/// Particula
/// </summary>
//std::unique_ptr<Particle> particle;

std::list<Projectile*> projectiles;

/// <summary>
/// Sistema de particulas
/// </summary>
std::unique_ptr<ParticleSystem> particleSystem;

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

	//particle = std::make_unique<Particle>(Vector3(10.0, 10.0, 0.0), Vector3(0.0, 10.0, 0.0), Vector3(0.0, 10.0, 0.0), 0.9);

	particleSystem = std::make_unique<ParticleSystem>();
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);

	//particle.get()->integrate(t);
	for (auto p : projectiles) p->integrate(t);

	particleSystem->update(t);
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

	for (auto shot : projectiles) 
	{
		if (shot != nullptr) 
		{
			delete shot;
			shot = nullptr;
		}
	}
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	case ' ':
	{
		break;
	}
	case 'P': // PISTOL
		projectiles.push_back(new Projectile(Projectile::PISTOL));
		break;
	case 'R': // ARTILLERY
		projectiles.push_back(new Projectile(Projectile::ARTILLERY));
		break;
	case 'B': // FIREBALL
		projectiles.push_back(new Projectile(Projectile::FIREBALL));
		break;
	case 'L': // LASER
		projectiles.push_back(new Projectile(Projectile::LASER));
		break;
	case 'F': // FIREWORK
		particleSystem.get()->shootFirework(0);
		break;
	case 'G': // GRAVITY
		particleSystem.get()->addGravityParticles();
		break;
	case 'N': // WIND
		particleSystem.get()->addWindParticles();
		break;
	case 'H': // WINDWHIRL
		particleSystem.get()->addWhirlwindParticles();
		break;
	case 'X': // EXPLOSION
		particleSystem.get()->addExplosionParticles();
		break;
	default: 
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
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