#pragma once

#include "RenderUtils.hpp"
#include "core.hpp"

#include <random>

#include "ParticleGenerator.h"

class UniformParticleGenerator : public ParticleGenerator
{
public:
	UniformParticleGenerator(string name, Vector3 pos, Vector3 vel, double genProb, Particle* model, Vector3 p, Vector3 v) :
		ParticleGenerator(name, pos, vel, genProb, model), _pos_width(p), _vel_width(v) {};

	virtual list<Particle*> generateParticles() override;

protected:
	Vector3 _vel_width, _pos_width;
};
