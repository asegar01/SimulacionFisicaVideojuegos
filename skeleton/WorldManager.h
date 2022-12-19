#pragma once

#include <string>
#include <random>
#include <list>

#include "RenderUtils.hpp"
#include "core.hpp"

#include "PxScene.h"
#include "PxPhysics.h"
#include "PxRigidDynamic.h"

using namespace physx;
using namespace std;

class SolidGenerator;
class GaussianSolidGenerator;

class WorldManager
{
public:
	WorldManager(PxScene* gScene, PxPhysics* gPhysics);
	~WorldManager() {};

	int getNumSolids() { return _num_solids; }

	void update(double t);

protected:
	PxScene* _gScene;
	PxPhysics* _gPhysics;
	int _num_solids = 10;
	list<PxRigidDynamic*> _solids;
	list<SolidGenerator*> _solid_generators;
	double _time_gen = 2.0;
	Vector3 size = { 5.0, 5.0, 5.0 };
};
