#pragma once

#include "RenderUtils.hpp"
#include "core.hpp"
#include <list>
#include <random>

#include "Particle.h"

class Particle;

class ParticleGenerator 
{
public:
	ParticleGenerator(string name, Vector3 pos, Vector3 vel, Particle* model) 
		: _name(name), _pos(pos), _vel(vel), _model(model), _numParticles(200) {};
	~ParticleGenerator() { delete _model; }

	virtual list<Particle*> generateParticles() = 0;

protected:
	string _name;
	Vector3 _pos, _vel;
	Particle* _model;
	int _numParticles;
};