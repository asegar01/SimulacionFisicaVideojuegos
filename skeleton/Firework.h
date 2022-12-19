#pragma once

#include "RenderUtils.hpp"
#include "core.hpp"

#include <list>
#include <memory>

#include "Particle.h"
#include "ParticleGenerator.h"

class Firework : public Particle
{
public:
	Firework(Vector3 pos, Vector3 vel, Vector3 acc, float damping, float mass, list<shared_ptr<ParticleGenerator>> generations)
		: Particle(ParticleType::FIREWORK, pos, vel, acc, damping, mass), _gens(generations) {};
	~Firework() {};

	virtual Firework* clone() const;

	list<Particle*> explode();

protected:
	list<shared_ptr<ParticleGenerator>> _gens;
};
