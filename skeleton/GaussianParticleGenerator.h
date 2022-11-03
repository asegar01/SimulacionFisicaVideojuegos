#pragma once

#include "RenderUtils.hpp"
#include "core.hpp"

#include <random>

#include "ParticleGenerator.h"

using namespace std;

class GaussianParticleGenerator : public ParticleGenerator
{
public:
	GaussianParticleGenerator(string name, Vector3 pos, Vector3 vel, double genProb, Particle* model, Vector3 p, Vector3 v, double time) :
		ParticleGenerator(name, pos, vel, genProb, model), std_dev_pos(p), std_dev_vel(v), std_dev_t(time) {};

	virtual list<Particle*> generateParticles() override;

protected:
	Vector3 std_dev_pos, std_dev_vel;
	double std_dev_t;
};
