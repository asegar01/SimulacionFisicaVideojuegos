#pragma once

#include "RenderUtils.hpp"
#include "core.hpp"

#include <memory>
#include <chrono>

#include <string>
#include <list>

using namespace physx;
using namespace std;

enum ParticleType
{
	SPHERE, BOX, CAPSULE
};

class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel);
	Particle(ParticleType type, Vector3 Pos, Vector3 Vel, Vector3 Acc, float Damping);
	~Particle() { DeregisterRenderItem(renderItem); };

	void integrate(double t);

	void setMass(float Mass) { mass = Mass; };
	void setPosition(Vector3 Pos) { pose.p = Pos; };
	void setVelocity(Vector3 Vel) { _vel = Vel; };
	void setAcceleration(Vector3 Acc) { _accel = Acc; };
	void setDamping(float Damping) { damping = Damping; };

	PxTransform getPosition() { return pose; };

	virtual Particle* clone() const;
	double getRemainingTime() { return _remaining_time; };
	void setRemainingTime(double time) { _remaining_time = time; };

protected:
	RenderItem* renderItem;

	float damping = 0.99f;
	float mass;

	ParticleType _type;
	double _remaining_time;
	PxTransform pose;
	Vector3 _vel;
	Vector3 _accel = { 0.0, -10.0, 0.0 };
};