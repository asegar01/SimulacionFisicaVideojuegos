#pragma once

#include "core.hpp"
#include "ForceGenerator.h"
#include "SolidForceGenerator.h"

class SpringForceGenerator : public ForceGenerator, public SolidForceGenerator
{
public:
	SpringForceGenerator(double k, double resting_length, Particle* other) 
		: _k(k), _resting_length(resting_length), _other(other) {};

	virtual void updateForce(Particle* particle, double t);
	virtual void updateForceRB(PxRigidDynamic* solid, double t);

	inline void setK(double k) { _k = k; }
	inline double getK() { return _k; }

	virtual ~SpringForceGenerator() {};

protected:
	double _k; // Elastic coef
	double _resting_length;

	Particle* _other;
};
