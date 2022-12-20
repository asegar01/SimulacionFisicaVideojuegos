#pragma once

#include "core.hpp"
#include "ForceGenerator.h"
#include "SolidForceGenerator.h"

class BuoyancyForceGenerator : public ForceGenerator, public SolidForceGenerator
{
public:
	BuoyancyForceGenerator(float h, float v, float d) : _height(h), _volume(v), _liquid_density(d)
	{ _liquid_particle = new Particle(PLANE, { 0.0, 30.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, 0.0f, 0.0f, 1e6); }

	virtual void updateForce(Particle* particle, double t);
	virtual void updateForceRB(PxRigidDynamic* solid, double t);

	inline void setVolume(float v) { _volume = v; }
	inline float getVolume() { return _volume; }

	virtual ~BuoyancyForceGenerator() { delete _liquid_particle; }

protected:
	float _height;
	float _volume;
	float _liquid_density;
	float _gravity = 9.8;

	Particle* _liquid_particle; // For representation
};
