#pragma once

#include "RenderUtils.hpp"
#include "core.hpp"

#include <memory>

using namespace physx;

class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel);
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, float Damping);
	~Particle();

	void integrate(double t);

	void setMass(float Mass) { mass = Mass; };
	void setVelocity(Vector3 Vel) { vel = Vel; };
	void setAcceleration(Vector3 Acc) { a = Acc; };
	void setDamping(float Damping) { damping = Damping; };

private:
	Vector3 vel;
	PxTransform pose;
	std::unique_ptr<RenderItem> renderItem;

	Vector3 a;
	float damping;

	float mass;
};