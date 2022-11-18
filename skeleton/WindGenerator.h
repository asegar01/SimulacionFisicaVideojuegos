#pragma once

#include "ParticleDragGenerator.h"

class WindGenerator : public ParticleDragGenerator
{
public:
	WindGenerator(const Vector3& vel, const float k1, const float k2, double x, double y, double z) 
		: ParticleDragGenerator(k1, k2), _vel(vel), _x(x), _y(y), _z(z) {};

	virtual void updateForce(Particle* particle, double t);
	inline void setWindVelocity(Vector3 v) { _vel = v; }

protected:
	// Velocidad del viento
	Vector3 _vel;

	// Area de accion
	double _x, _y, _z;
};
