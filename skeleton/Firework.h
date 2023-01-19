#pragma once

#include "Particle.h"
#include "ParticleGenerator.h"

class Firework : public Particle
{
public:
	Firework(Vector3 pos, Vector3 vel, Vector3 acc, float mass, float damping, double time, list<shared_ptr<ParticleGenerator>> generations)
		: Particle(ParticleType::FIREWORK, pos, vel, acc, mass, damping, time), _generations(generations) {};
	~Firework() {};

	virtual Firework* clone() const;

	list<Particle*> explode();

protected:
	list<shared_ptr<ParticleGenerator>> _generations;
};
