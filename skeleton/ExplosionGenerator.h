#pragma once

#include "ForceGenerator.h"
#include "SolidForceGenerator.h"

#include <cmath>

class ExplosionGenerator : public ForceGenerator, public SolidForceGenerator
{
public:
	ExplosionGenerator(const Vector3& e, float r, float k) : _origin(e), _r(r), _k(k), _time(0.0) {};

	virtual void updateForce(Particle* particle, double t);
	virtual void updateForceRB(PxRigidDynamic* solid, double t);

	void addTime(float t) { _time += t; }

protected:
	// Origen de la explosion
	Vector3 _origin;

	// Radio de la explosion
	float _r;

	// Intensidad de la explosion
	float _k;

	float _time;

	// Tiempo de accion
	double _remaining_time = 5;
};
