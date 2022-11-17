#pragma once

#include "core.hpp"
#include "ForceGenerator.h"

class GravityForceGenerator : public ForceGenerator
{
public:
	GravityForceGenerator(const Vector3& g) : _gravity(g) {};

	virtual void updateForce(Particle* particle, double t);

	inline void setGravity(Vector3 g) { _gravity = g; }

protected:
	Vector3 _gravity;
};
