#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() : _particles(0)
{
	// Particula uniforme
	_particle_generators.push_back(new UniformParticleGenerator("uniform", { 10.0, 20.0, 10.0 }, { 5.0, -10.0, 5.0 } , 0.5, 
		new Particle({ 5.0, 5.0, 5.0 }, { 10.0, 10.0, 0.0 }), { 10.0, 10.0, 0.0 }, { 5.0, 5.0, 5.0 }));

	// Particula gaussiana
	/*_particle_generators.push_back(new GaussianParticleGenerator("gaussian", { 10.0, 20.0, 10.0 }, { 5.0, -10.0, 5.0 }, 0.5, 
		new Particle({ 5.0, 5.0, 5.0 }, { 10.0, 10.0, 0.0 }), { 10.0, 10.0, 10.0 }, { 5.0, 5.0, 5.0 }, 5.0));*/
}

ParticleSystem::~ParticleSystem() 
{
	/*auto p = _particles.begin();
	while (p != _particles.end()) 
	{
		delete (*p);
		(p) = _particles.erase(p);
	}*/

	while (!_particles.empty()) 
	{
		delete _particles.front();
		_particles.pop_front();
	}

	/*auto g = _particle_generators.begin();
	while (g != _particle_generators.end()) 
	{
		delete (*g);
		(g) = _particle_generators.erase(g);
	}*/

	while (!_particles.empty()) 
	{
		delete _particles.front();
		_particles.pop_front();
	}
}

void ParticleSystem::update(double t) 
{
	for (auto p = _particle_generators.begin(); p != _particle_generators.end(); ++p) 
	{
		if (_particles.size() < 10) 
		{
			auto l = (*p)->generateParticles();

			for (auto q = l.begin(); q != l.end(); ++q)
				_particles.push_back((*q));
		}
	}

	// Update de cada particula
	auto p = _particles.begin();
	while (p != _particles.end())
	{
		(*p)->integrate(t);

		// Remueve la particula si es invalida
		if ((*p)->getPosition().p.y < 0.0f ||
			(*p)->getRemainingTime() < 0 ||
			(*p)->getPosition().p.z > 200.0f)
		{
			delete (*p);
			p = _particles.erase(p);
		}
		else ++p;
	}
}

ParticleGenerator* ParticleSystem::getParticleGenerator(string name) 
{
	for (auto p : _particle_generators) 
		if (p->getName() == name) return p;
}