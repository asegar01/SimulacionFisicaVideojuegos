#include "Firework.h"

Firework* Firework::clone() const 
{
	Firework* f = new Firework(_pos.p, _vel, _acc, _mass, _damping, _time, _generations);
	return f;
}

list<Particle*> Firework::explode() 
{
	list<Particle*> generations;

	for (auto g : _generations) 
	{
		auto particles = g->generateParticles();

		for (auto p : particles)
			generations.push_back(p);
	}

	return generations;
}