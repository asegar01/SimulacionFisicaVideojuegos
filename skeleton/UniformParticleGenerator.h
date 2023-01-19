#pragma once

#include "RenderUtils.hpp"
#include "core.hpp"

#include <random>

#include "ParticleGenerator.h"

class UniformParticleGenerator : public ParticleGenerator
{
public:
	UniformParticleGenerator(string name, Vector3 pos, Vector3 vel, Particle* model, Vector3 p, Vector3 v)
		: ParticleGenerator(name, pos, vel, model), _posWidth(p), _velWidth(v) {};

	virtual list<Particle*> generateParticles() override;

protected:
	Vector3 _posWidth, _velWidth;
};
