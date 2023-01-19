#pragma once

#include "SolidDragGenerator.h"

class WindGenerator : public SolidDragGenerator
{
public:
	WindGenerator(const float k1, const float k2) : SolidDragGenerator(k1, k2) {};
	WindGenerator(const Vector3& w, const float k1, const float k2, double x, double y, double z, double offset)
		: SolidDragGenerator(k1, k2), _vel(w), _x(x), _y(y), _z(z), _offset(offset) {};

	virtual void updateForceRB(PxRigidDynamic* solid, double t);
	inline void setWindVelocity(Vector3 v) { _vel = v; }

protected:
	// Velocidad del viento
	Vector3 _vel;

	// Area de accion
	double _x, _y, _z;

	// Offset
	double _offset;
};
