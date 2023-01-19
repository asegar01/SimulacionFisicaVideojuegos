#pragma once

#include "SolidForceGenerator.h"

class ExplosionGenerator : public SolidForceGenerator
{
public:
	ExplosionGenerator(const Vector3& e, float r, float k) : _origin(e), _r(r), _k(k), _time(0.0), _timeLeft(1.0) {};

	virtual void updateForceRB(PxRigidDynamic* solid, double t);
	void addTime(double t) { _time += t; }
	double getTime() { return _time; }

protected:
	// Origen de la explosion
	Vector3 _origin;

	// Radio de la explosion
	float _r;

	// Intensidad de la explosion
	float _k;

	// Tiempo transcurrido
	double _time;

	// Tiempo de accion
	double _timeLeft;
};
