#pragma once

#include "RenderUtils.hpp"
#include "core.hpp"
#include <list>
#include <random>

#include "RigidBody.h"
#include "WorldManager.h"

using namespace physx;
using namespace std;

class SolidGenerator
{
public:
	SolidGenerator(string name, Vector3 vel, RigidBody* model, WorldManager* worldManager, PxPhysics* gPhysics) : 
		_name(name), _mean_vel(vel), _model(model), _worldManager(worldManager), _gPhysics(gPhysics) {};
	~SolidGenerator() {};

	// Establece el tipo de solido
	void setSolid(RigidBody* model) { _model = model; }
	string getName() { return _name; }
	RigidBodyType getType() { return _model->getType(); }

	virtual PxRigidDynamic* generateSolids() = 0;

protected:
	string _name;
	Vector3 _mean_vel;
	RigidBody* _model;
	WorldManager* _worldManager;
	PxPhysics* _gPhysics;
};