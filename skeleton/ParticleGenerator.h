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
	ParticleGenerator(string name, Vector3 pos, Vector3 vel, double genProb, Particle* model) :
		_name(name), _mean_pos(pos), _mean_vel(vel), _generation_probability(genProb), _model(model) {};
	~ParticleGenerator() { delete _model; };

	// Establece el tipo de particula
	void setParticle(Particle* model) { _model = model; };
	string getName() { return _name; };
	int getNumParticles() { return _num_particles; };

	virtual list<Particle*> generateParticles() = 0;

protected:
	string _name;
	Vector3 _mean_pos, _mean_vel;
	double _generation_probability;
	int _num_particles = 10;
	Particle* _model;
};
