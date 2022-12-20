#pragma once

#include <iostream>

#include "core.hpp"
#include "ForceGenerator.h"
#include "SolidForceGenerator.h"

using namespace std;

class ParticleDragGenerator : public ForceGenerator, public SolidForceGenerator
{
public:
	ParticleDragGenerator() {};
	ParticleDragGenerator(const float k1, const float k2) : _k1(k1), _k2(k2) {};

	virtual void updateForce(Particle* particle, double t);
	virtual void updateForceRB(PxRigidDynamic* solid, double t);
	inline void setDrag(float k1, float k2) { _k1 = k1; _k2 = k2; }
	inline float getK1() { return (_k1); }
	inline float getK2() { return (_k2); }

protected:
	float _k1; // Coef for velocity
	float _k2; // Coef for square velocity
};
