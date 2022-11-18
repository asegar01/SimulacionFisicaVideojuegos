#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() : _particles(0)
{
	// Particula uniforme
	/*_particle_generators.push_back(new UniformParticleGenerator("uniform", { 10.0, 20.0, 10.0 }, { 5.0, -10.0, 5.0 } , 0.5, 
		new Particle({ 5.0, 5.0, 5.0 }, { 10.0, 10.0, 0.0 }), { 10.0, 10.0, 0.0 }, { 5.0, 5.0, 5.0 }));*/

	// Particula gaussiana
	/*_particle_generators.push_back(new GaussianParticleGenerator("gaussian", { 10.0, 20.0, 10.0 }, { 5.0, -10.0, 5.0 }, 0.5, 
		new Particle({ 5.0, 5.0, 5.0 }, { 10.0, 10.0, 0.0 }), { 10.0, 10.0, 10.0 }, { 5.0, 5.0, 5.0 }, 5.0));*/

	/*_firework_gen.push_back(shared_ptr<ParticleGenerator>(new GaussianParticleGenerator("fireworks", { 0.0, 20.0, 0.0 }, { 20, 10, 20 }, 1.0, 
		_fireworks_pool[0], {2.0, 1.0, 2.0}, {1.0, 1.0, 1.0}, 1.0)));*/

	//generateFireworkSystem();

	pFR = make_unique<ParticleForceRegistry>();
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

	while (!_particle_generators.empty()) 
	{
		delete _particle_generators.front();
		_particle_generators.pop_front();
	}
}

void ParticleSystem::update(double t) 
{
	if(_particle_generators.size() != 0)
	for (auto p : _particle_generators) 
	{
		if (_particles.size() < 10) 
		{
			auto l = (p)->generateParticles();

			for (auto q = l.begin(); q != l.end(); ++q)
				_particles.push_back((*q));
		}
	}	

	// Actualiza cada particula
	auto p = _particles.begin();
	while (p != _particles.end())
	{
		(*p)->integrate(t);

		// Remueve la particula si es invalida
		if ((*p)->getPosition().p.y < 0.0f ||
			(*p)->getRemainingTime() < 0 ||
			(*p)->getPosition().p.z > 200.0f)
		{
			onParticleDeath(*p);

			delete (*p);
			p = _particles.erase(p);
		}
		else ++p;
	}

	// Actualiza las fuerzas
	pFR.get()->updateForces(t);

	// Actualiza el tiempo de explosion
	if (explode) eFG->addTime(t);
}

ParticleGenerator* ParticleSystem::getParticleGenerator(string name) 
{
	for (auto p : _particle_generators) 
		if ((p)->getName() == name) return p;
}

void ParticleSystem::generateFireworkSystem()
{
	//auto a = new Firework(Vector3(10, 10, 0), Vector3(0, 15, 0), Vector3(0, 1, 0), 0.99f, _firework_gen);
	//_fireworks_pool.push_back(new Firework(Vector3(10, 10, 0), Vector3(0, 15, 0), Vector3(0, 1, 0), 0.99f, _firework_gen));

	// Se crea un generador de particulas - gaussiano
	// Se copian y modifican las propiedades
	// Push back pool fireworks de new firework
	shared_ptr<ParticleGenerator> pG1(new GaussianParticleGenerator("gaussian", { 10.0, 20.0, 10.0 }, { 5.0, -10.0, 5.0 }, 0.5,
		new Particle({ 5.0, 5.0, 5.0 }, { 10.0, 10.0, 0.0 }), { 10.0, 10.0, 10.0 }, { 5.0, 5.0, 5.0 }, 5.0));
	_fireworks_pool.push_back(new Firework({ 0.0, 0.0, 0.0 }, { 0.0, 30.0, 0.0 }, { 0.0, -10.0, 0.0 }, 0.99, { pG1 }));
}

void ParticleSystem::shootFirework(int type)
{
	Firework* f;
	f = _fireworks_pool[type]->clone();
	f->setPosition({ 0, 0, 0 });
	_particles.push_back(f);
}

void ParticleSystem::onParticleDeath(Particle* p) 
{
	// Comprueba si la particula p es tipo firework
	if (p->getType() == FIREWORK) 
	{
		Firework* f = dynamic_cast<Firework*>(p);
		if (f != nullptr) {
			f->explode();
			for (auto p : f->explode())
				_particles.push_back(p);
		}
	}
}

void ParticleSystem::addGravityParticles() 
{
	auto p = new Projectile(Projectile::PISTOL);
	p->setPosition({ 0.0, 50.0, 0.0 });
	p->setVelocity({ 50.0, 0.0, 0.0 });
	p->setAcceleration({ 0.0, 0.0, 0.0 });
	p->setMass(50.0f);
	p->setDamping(0.1f);
	p->setRemainingTime(5.0);
	_particles.push_back(p);

	auto p2 = new Projectile(Projectile::PISTOL);
	p2->setPosition({ 20.0, 50.0, 0.0 });
	p2->setVelocity({ 50.0, 0.0, 0.0 });
	p2->setAcceleration({ 0.0, 0.0, 0.0 });
	p2->setMass(50.0f);
	p2->setDamping(0.9f);
	p2->setRemainingTime(5.0);
	_particles.push_back(p2);

	auto gFG = new GravityForceGenerator({ 0.0, -9.8, 0.0 });

	pFR.get()->addRegistry(gFG, p);
	pFR.get()->addRegistry(gFG, p2);
}

void ParticleSystem::addWindParticles() 
{
	auto p = new Projectile(Projectile::PISTOL);
	p->setPosition({ 0.0, 40.0, 0.0 });
	p->setVelocity({ 30.0, 0.0, 0.0 });
	p->setAcceleration({ 0.0, 0.0, 0.0 });
	p->setMass(50.0f);
	p->setRemainingTime(5.0);
	_particles.push_back(p);

	auto p2 = new Projectile(Projectile::PISTOL);
	p2->setPosition({ -20.0, 40.0, 0.0 });
	p2->setVelocity({ 30.0, 0.0, 0.0 });
	p2->setAcceleration({ 0.0, 0.0, 0.0 });
	p2->setMass(100.0f);
	p2->setRemainingTime(5.0);
	_particles.push_back(p2);

	auto wFG = new WindGenerator({ -10.0, 10.0, 0.0 }, 0.1, 0.0, 50.0, 50.0, 50.0);

	pFR.get()->addRegistry(wFG, p);
	pFR.get()->addRegistry(wFG, p2);
}

void ParticleSystem::addWhirlwindParticles() 
{
	auto p = new Projectile(Projectile::PISTOL);
	p->setPosition({ 0.0, 0.0, 0.0 });
	p->setVelocity({ 0.0, 0.0, 0.0 });
	p->setAcceleration({ 0.0, 0.0, 0.0 });
	p->setMass(50.0f);
	p->setRemainingTime(10.0f);
	_particles.push_back(p);

	auto whFG = new WhirlwindGenerator({ 10.0, 0.0, 10.0 }, 0.1, 0.2);

	pFR.get()->addRegistry(whFG, p);
}

void ParticleSystem::addExplosionParticles() 
{
	explode = true;

	eFG = new ExplosionGenerator({ 0.0, 0.0, 0.0 }, 100.0, 100.0);

	for (auto p : _particles)
		pFR.get()->addRegistry(eFG, p);
}