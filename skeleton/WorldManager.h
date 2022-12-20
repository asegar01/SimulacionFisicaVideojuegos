#pragma once

#include <string>
#include <random>
#include <list>

#include "RenderUtils.hpp"
#include "core.hpp"

#include "PxScene.h"
#include "PxPhysics.h"
#include "PxRigidDynamic.h"
#include "SolidForceRegistry.h"
#include "SpringForceGenerator.h"
#include "AnchoredSpringFG.h"
#include "WindGenerator.h"
#include "WhirlwindGenerator.h"
#include "ExplosionGenerator.h"
#include "BuoyancyForceGenerator.h"

using namespace physx;
using namespace std;

class SolidGenerator;
class GaussianSolidGenerator;

class WorldManager
{
public:
	WorldManager(PxScene* gScene, PxPhysics* gPhysics) : _gScene(gScene), _gPhysics(gPhysics) { sFR = make_unique<SolidForceRegistry>(); }
	~WorldManager() {};

	int getNumSolids() { return _num_solids; }

	void createScene();
	void update(double t);

	// Viento
	void generateWind();

	// Torbellino
	void generateWhirlwind();

	// Explosion
	void generateExplosion();

	// Muelle
	void generateSpring();
	void increase();
	void decrease();

	// Flotabilidad
	void generateBuoyancy();
	inline void increaseMass() { buoyancySolid->setMass(buoyancySolid->getMass() + 1.0f); }
	inline void decreaseMass() { if (buoyancySolid->getMass() > 1.0f) buoyancySolid->setMass(buoyancySolid->getMass() - 1.0f); };

protected:
	PxScene* _gScene;
	PxPhysics* _gPhysics;
	int _num_solids = 10;
	list<PxRigidDynamic*> _solids;
	list<SolidGenerator*> _solid_generators;
	double _time_gen = 2.0;
	Vector3 size = { 5.0, 5.0, 5.0 };
	unique_ptr<SolidForceRegistry> sFR;

	// Explosion
	ExplosionGenerator* eFG = nullptr;
	bool explode = false;

	// Muelle
	PxRigidDynamic* springSolid = nullptr;
	AnchoredSpringFG* aSFG = nullptr;

	// Flotabilidad
	PxRigidDynamic* buoyancySolid = nullptr;
	BuoyancyForceGenerator* bFG = nullptr;

	bool springActive = false;
	bool buoyancyActive = false;
};
