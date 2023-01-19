#include "ParticleSystem.h"

void ParticleSystem::update(double t) 
{
	// Actualiza cada particula
	auto p = _particles.begin();
	while (p != _particles.end()) 
	{
		(*p)->integrate(t);

		// Remueve la particula si es invalida
		if ((*p)->getPosition().y < 0.0f ||
			(*p)->getPosition().z > 200.0f ||
			(*p)->getRemainingTime() < 0.0)
		{
			onParticleDeath((*p));

			delete (*p);
			p = _particles.erase(p);
		}
		else ++p;
	}

	
}

void ParticleSystem::generateFirework()
{
	shared_ptr<ParticleGenerator> fPG(new UniformParticleGenerator("uniform", { 80.0, 20.0, -150.0 }, { 0.0, 10.0, 0.0 },
		new Particle(UNUSED, { 80.0, 5.0, -150.0 }, { 0.0, 10.0, 0.0 }, { 0.0, -9.8, 0.0 }, 0.3f, 0.99f, 5.0f), { 5.0, 5.0, 5.0 }, { 5.0, 5.0, 5.0 }));
	_fireworksPool.push_back(new Firework({ 80.0, 0.0, -150.0 }, { 0.0, 20.0, 0.0 }, { 0.0, -9.8, 0.0 }, 0.3f, 0.99f, 2.0, { fPG }));
}

void ParticleSystem::shootFirework(int type) 
{
	Firework* f;
	f = _fireworksPool[type]->clone();
	f->setPosition({ 80.0, 0.0, -150.0 });
	_particles.push_back(f);
}

void ParticleSystem::onParticleDeath(Particle* p)
{
	// Comprueba si la particula p es tipo firework
	if (p->getType() == FIREWORK) 
	{
		Firework* f = dynamic_cast<Firework*>(p);
		if (f != nullptr) 
		{
			auto generations = f->explode();
			for (auto p : generations)
				_particles.push_back(p);
		}
	}
}