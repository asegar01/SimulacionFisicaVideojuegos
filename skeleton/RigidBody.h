#pragma once

#include "RenderUtils.hpp"
#include "core.hpp"
#include "PxRigidDynamic.h"

#include <memory>
#include <chrono>

#include <string>
#include <list>
#include <cmath>

using namespace physx;
using namespace std;

enum RigidBodyType 
{
	RBSPHERE, RBBOX
};

class RigidBody
{
public:
	RigidBody(RigidBodyType type, Vector3 pos, Vector3 vel, PxPhysics* gPhysics) : _type(type), _pos(pos), _vel(vel) {};
	RigidBody(RigidBodyType type, Vector3 pos, Vector3 vel, Vector3 angularVel, Vector3 material, PxReal density, PxPhysics* gPhysics) 
		: _type(type), _pos(pos), _vel(vel), _angularVel(angularVel), _material(material), _density(density), _gPhysics(gPhysics) {};
	~RigidBody() {};

	virtual void integrate(double t) {};
	virtual PxRigidDynamic* clone() const 
	{
		PxRigidDynamic* solid = _gPhysics->createRigidDynamic(PxTransform({ 0.0, 50.0, 0.0 }));
		return solid;
	};

	Vector3 getPosition() { return _pos.p; }
	Vector3 getVelocity() { return _vel; }
	RigidBodyType getType() { return _type; }

private:
	PxTransform _pos;
	Vector3 _vel, _angularVel, _material;
	PxReal _density;
	RigidBodyType _type;
	PxPhysics* _gPhysics;
};
