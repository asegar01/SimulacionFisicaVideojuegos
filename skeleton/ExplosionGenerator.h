#pragma once

#include "ForceGenerator.h"

#include <cmath>

class ExplosionGenerator : public ForceGenerator
{
public:
	ExplosionGenerator(const Vector3& e, float r, float k) : _origin(e), _r(r), _k(k), _time(0.0) {};

	virtual void updateForce(Particle* particle, double t);

	void addTime(float t) { _time += t; }

protected:
	// Origen de la explosion
	Vector3 _origin;

	// Radio de la explosion
	float _r;

	// Intensidad de la explosion
	float _k;

	float _time;
};
