#include "Firework.h"

Firework* Firework::clone() const 
{
	Firework* f = new Firework(pose.p, _vel, _accel, damping, mass, _gens);
	return f;
}

list<Particle*> Firework::explode() 
{
	list<Particle*> generations;

	for (auto g : _gens) 
	{
		auto particles = g->generateParticles();
		for (auto q : particles)
			generations.push_back(q);
	}

	return generations;
}