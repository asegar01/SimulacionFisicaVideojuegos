#pragma once

#include "RenderUtils.hpp"
#include "core.hpp"

#include <memory>
#include <chrono>

#include <string>
#include <list>
#include <cmath>

using namespace physx;
using namespace std;

enum ParticleType
{
	SPHERE, BOX, CAPSULE, FIREWORK
};

class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel);
	Particle(ParticleType type, Vector3 Pos, Vector3 Vel, Vector3 Acc, float Damping, float mass);
	~Particle() { /*DeregisterRenderItem(renderItem);*/ };

	void integrate(double t);

	void setMass(float Mass) { mass = Mass; };
	void setPosition(Vector3 Pos) { pose.p = Pos; };
	void setVelocity(Vector3 Vel) { _vel = Vel; };
	void setAcceleration(Vector3 Acc) { _accel = Acc; };
	void setDamping(float Damping) { damping = Damping; };
	void setType(ParticleType type);

	PxTransform getPosition() { return pose; };
	Vector3 getVel() { return _vel; }
	ParticleType getType() { return _type; }

	virtual Particle* clone() const;
	double getRemainingTime() { return _remaining_time; };
	void setRemainingTime(double time) { _remaining_time = time; };

	// Get particle mass
	float getMass() { return mass; }
	float getInverseMass() { return 1 / mass; }

	// Clears accumulated force
	void clearForce() { force = Vector3(0); };

	// Add force to apply in next integration only
	void addForce(const Vector3& f) { force += f; };

protected:
	RenderItem* renderItem;

	float damping = 0.99f;
	float mass = 1.0f;

	ParticleType _type;
	double _remaining_time;
	PxTransform pose;
	Vector3 _vel;
	Vector3 _accel = { 0.0, -10.0, 0.0 };

	// Accumulated force
	Vector3 force = { 0.0, 0.0, 0.0 };
};