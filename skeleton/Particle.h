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

private:
	Vector3 vel;
	PxTransform pose;
	std::unique_ptr<RenderItem> renderItem;

	Vector3 a;
	float damping;
};