#pragma once

#include "SolidGenerator.h"

class GaussianSolidGenerator : public SolidGenerator
{
public:
	GaussianSolidGenerator(string name, Vector3 vel, RigidBody* model, Vector3 p, Vector3 v, PxPhysics* gPhysics, WorldManager* worldManager) :
		SolidGenerator(name, vel, model, worldManager, gPhysics), std_dev_vel(v) {};

	virtual PxRigidDynamic* generateSolids() override;

protected:
	Vector3 std_dev_vel;
};
