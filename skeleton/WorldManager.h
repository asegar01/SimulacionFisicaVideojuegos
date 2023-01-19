#pragma once

#include <string>
#include <random>
#include <list>
#include <chrono>

#include "RenderUtils.hpp"
#include "core.hpp"
#include "PxScene.h"
#include "PxPhysics.h"
#include "PxRigidDynamic.h"
#include "SolidForceRegistry.h"
#include "WindGenerator.h"
#include "BuoyancyGenerator.h"
#include "ExplosionGenerator.h"

using namespace physx;
using namespace std;

enum CurrentScene
{
	SCENE0, SCENE1, SCENE2, SCENE3, SCENE4
};

class WorldManager
{
public:
	WorldManager(PxScene* gScene, PxPhysics* gPhysics) : _gScene(gScene), _gPhysics(gPhysics), _currentScene(SCENE0), _nextSceneActive(false), 
		_explode(false), _activeCooldown(false), _cooldownTime(0.0) { sFR = make_unique<SolidForceRegistry>(); };
	~WorldManager() {};

	// Escena general
	void createWorldScene();

	// Acceder a la siguiente escena
	void nextScene();
	void changeSceneActive() { _nextSceneActive = !_nextSceneActive; }
	bool getLastScene() { return _currentScene == SCENE4; }

	void createScene01();
	void createScene02();
	void createScene03();
	void createScene04();

	void addForce(Vector3 v);

	// Reiniciar posicion pelota
	void setBallStart();

	// Establecer la posicion de la meta
	void setGoalStart(float x);

	// Creacion de plataforma
	void createPlatform(float x);

	// Creacion de explosivos
	void createExplosive(float x, float z);
	void generateExplosion(PxActor* actor);

	void update(double t);

	PxRigidDynamic* getFollowActor() { if(ball != nullptr) return ball; }

protected:
	PxScene* _gScene;
	PxPhysics* _gPhysics;

	// Pelota de golf
	PxRigidDynamic* ball = nullptr;

	// Meta
	PxRigidStatic* goalLower = nullptr;
	PxRigidStatic* goalUpper = nullptr;

	// Gestion de escenas
	CurrentScene _currentScene;
	bool _nextSceneActive;

	// Generadores de fuerzas
	unique_ptr<SolidForceRegistry> sFR;

	// Explosion
	PxActor* _actor = nullptr;
	ExplosionGenerator* eSFG = nullptr;
	bool _explode;

	// Tiempo de cooldown para los disparos
	bool _activeCooldown;
	double _cooldownTime;
	double _cooldown;
};
