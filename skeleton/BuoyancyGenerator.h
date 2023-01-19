#pragma once

#include "SolidForceGenerator.h"
#include "Particle.h"

class BuoyancyGenerator : public SolidForceGenerator
{
public:
	BuoyancyGenerator(float h, float v, float d, Vector3 pos, float offset) : _height(h), _volume(v), _liquidDensity(d), _gravity(9.8), _pos(pos), _offset(offset)
	{ _liquidParticle = new Particle(WATER, _pos, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, 0.0f, 0.0f, 1e6); }
	virtual ~BuoyancyGenerator() { delete _liquidParticle; }
	
	virtual void updateForceRB(PxRigidDynamic* solid, double t);

protected:
	float _height;
	float _volume;
	float _liquidDensity;
	float _gravity;

	// For representation
	Particle* _liquidParticle = nullptr;

	Vector3 _pos;
	float _offset;
};
