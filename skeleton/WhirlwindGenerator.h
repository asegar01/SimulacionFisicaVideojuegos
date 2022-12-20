#pragma once

#include "WindGenerator.h"

class WhirlwindGenerator : public WindGenerator
{
public:
	WhirlwindGenerator(const Vector3& w, const float k1, const float k2) : WindGenerator(k1, k2), _origin(w), K(1.0f) {};

	virtual void updateForce(Particle* particle, double t);
	virtual void updateForceRB(PxRigidDynamic* solid, double t);

protected:
	// Origen del torbellino
	Vector3 _origin;

	// Fuerza del torbellino
	float K;
};
