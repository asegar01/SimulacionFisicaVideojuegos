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
		if ((*p)->getPosition().p.y < -200.0f ||
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

void ParticleSystem::increase() 
{
	if(springActive)
		aSFG->setK(aSFG->getK() + 0.1);

	if (buoyancyActive)
		bFG->setVolume(bFG->getVolume() + 10.0f);
}

void ParticleSystem::decrease() 
{
	if (springActive && aSFG->getK() > 1.0)
		aSFG->setK(aSFG->getK() - 0.1);

	if (buoyancyActive && bFG->getVolume() > 10.0f)
		bFG->setVolume(bFG->getVolume() - 10.0f);
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
	Particle* p1 = new Particle(SPHERE, { -10.0, 50.0, 0.0 }, { 10.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, 0.3f, 50.0f, 5.0f);
	Particle* p2 = new Particle(SPHERE, { 10.0, 50.0, 0.0 }, { 10.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, 0.9f, 100.0f, 5.0f);

	GravityForceGenerator* gFG = new GravityForceGenerator({ 0.0, -9.8, 0.0 });
	pFR.get()->addRegistry(gFG, p1);
	pFR.get()->addRegistry(gFG, p2);

	_force_generators.push_back(gFG);
	_particles.push_back(p1);
	_particles.push_back(p2);
}

void ParticleSystem::addWindParticles() 
{
	Particle* p1 = new Particle(SPHERE, { 0.0, 40.0, 0.0 }, { 30.0, 0.0, 0.0 }, { 0.0 , 0.0, 0.0 }, 0.9f, 2.0f, 10.0f);
	Particle* p2 = new Particle(SPHERE, { -20.0, 40.0, 0.0 }, { 30.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, 0.9f, 5.0f, 10.0f);

	WindGenerator* wFG = new WindGenerator({ -200.0, 50.0, 0.0 }, 0.3, 0.0, 50.0, 50.0, 50.0);
	pFR.get()->addRegistry(wFG, p1);
	pFR.get()->addRegistry(wFG, p2);

	_force_generators.push_back(wFG);
	_particles.push_back(p1);
	_particles.push_back(p2);
}

void ParticleSystem::addWhirlwindParticles() 
{
	Particle* p = new Particle(SPHERE, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, 0.3f, 2.0f, 30.0f);

	WhirlwindGenerator* whFG = new WhirlwindGenerator({ 5.0, 0.0, 5.0 }, 0.1, 0.2);
	pFR.get()->addRegistry(whFG, p);

	_force_generators.push_back(whFG);
	_particles.push_back(p);
}

void ParticleSystem::addExplosionParticles() 
{
	explode = true;

	eFG = new ExplosionGenerator({ 0.0, 0.0, 0.0 }, 100.0, 100.0);
	for (auto p : _particles)
		pFR.get()->addRegistry(eFG, p);
}

void ParticleSystem::generateSpringDemo() 
{
	Particle* p1 = new Particle(SPHERE, { -10.0, 10.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, 0.85, 2.0f, 60.0f);
	Particle* p2 = new Particle(SPHERE, { 10.0, 10.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, 0.85, 2.0f, 60.0f);

	SpringForceGenerator* f1 = new SpringForceGenerator(1, 10, p2);
	pFR.get()->addRegistry(f1, p1);
	SpringForceGenerator* f2 = new SpringForceGenerator(1, 10, p1);
	pFR.get()->addRegistry(f2, p2);

	_force_generators.push_back(f1);
	_force_generators.push_back(f2);
	_particles.push_back(p1);
	_particles.push_back(p2);

	// Then one spring with one fixed side
	springParticle = new Particle(SPHERE, { -10.0, 60.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, 0.85, 2.0f, 60.0f);

	aSFG = new AnchoredSpringFG(2, 10, { 10.0, 60.0, 0.0 });
	pFR.get()->addRegistry(aSFG, springParticle);
	GravityForceGenerator* f4 = new GravityForceGenerator({ 0.0, -9.8, 0.0 });
	pFR.get()->addRegistry(f4, springParticle);

	_force_generators.push_back(aSFG);
	_force_generators.push_back(f4);
	_particles.push_back(springParticle);

	springActive = !springActive;
}

void ParticleSystem::generateWindSpringDemo() 
{
	WindGenerator* whS = new WindGenerator({ -100.0, 50.0, 0.0 }, 0.3, 0.0, 100.0, 100.0, 100.0);
	pFR.get()->addRegistry(whS, springParticle);

	_force_generators.push_back(whS);
}

void ParticleSystem::generateSlinky() 
{
	Particle* p1 = new Particle(SPHERE, { 0.0, 40.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, 0.85, 2.0f, 60.0f);
	Particle* p2 = new Particle(SPHERE, { 0.0, 30.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, 0.85, 2.0f, 60.0f);
	Particle* p3 = new Particle(SPHERE, { 0.0, 20.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, 0.85, 2.0f, 60.0f);
	Particle* p4 = new Particle(SPHERE, { 0.0, 10.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, 0.85, 2.0f, 60.0f);
	Particle* p5 = new Particle(SPHERE, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, 0.85, 2.0f, 60.0f);

	AnchoredSpringFG* f1 = new AnchoredSpringFG(5, 10, { 0.0, 50.0, 0.0 });
	pFR.get()->addRegistry(f1, p1);
	SpringForceGenerator* f2 = new SpringForceGenerator(5, 10, p2);
	pFR.get()->addRegistry(f2, p1);
	SpringForceGenerator* f3 = new SpringForceGenerator(5, 10, p1);
	pFR.get()->addRegistry(f3, p2);
	SpringForceGenerator* f4 = new SpringForceGenerator(5, 10, p3);
	pFR.get()->addRegistry(f4, p2);
	SpringForceGenerator* f5 = new SpringForceGenerator(5, 10, p2);
	pFR.get()->addRegistry(f5, p3);
	SpringForceGenerator* f6 = new SpringForceGenerator(5, 10, p4);
	pFR.get()->addRegistry(f6, p3);
	SpringForceGenerator* f7 = new SpringForceGenerator(5, 10, p3);
	pFR.get()->addRegistry(f7, p4);
	SpringForceGenerator* f8 = new SpringForceGenerator(5, 10, p5);
	pFR.get()->addRegistry(f8, p4);
	SpringForceGenerator* f9 = new SpringForceGenerator(5, 10, p4);
	pFR.get()->addRegistry(f9, p5);
	GravityForceGenerator* f10 = new GravityForceGenerator({ 0.0, -9.8, 0.0 });
	pFR.get()->addRegistry(f7, p1);
	pFR.get()->addRegistry(f7, p2);
	pFR.get()->addRegistry(f7, p3);
	pFR.get()->addRegistry(f7, p4);
	pFR.get()->addRegistry(f7, p5);

	_force_generators.push_back(f1);
	_force_generators.push_back(f2);
	_force_generators.push_back(f3);
	_force_generators.push_back(f4);
	_force_generators.push_back(f5);
	_force_generators.push_back(f6);
	_force_generators.push_back(f7);
	_force_generators.push_back(f8);
	_force_generators.push_back(f9);
	_force_generators.push_back(f10);
	_particles.push_back(p1);
	_particles.push_back(p2);
	_particles.push_back(p3);
	_particles.push_back(p4);
	_particles.push_back(p5);
}

void ParticleSystem::generateBuoyancy() 
{
	buoyancyParticle = new Particle(SPHERE, { 0.0, 40.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, 0.85, 10.0f, 60.0f);

	// Agua
	bFG = new BuoyancyForceGenerator(1.0, 100.0, 100.0); 
	pFR.get()->addRegistry(bFG, buoyancyParticle);
	// Aceite
	/*bFG = new BuoyancyForceGenerator(1.0, 100.0, 1.0);
	pFR.get()->addRegistry(bFG, buoyancyParticle);*/
	GravityForceGenerator* gFG = new GravityForceGenerator({ 0.0, -9.8, 0.0 });
	pFR.get()->addRegistry(gFG, buoyancyParticle);

	_force_generators.push_back(bFG);
	_force_generators.push_back(gFG);
	_particles.push_back(buoyancyParticle);

	buoyancyActive = !buoyancyActive;
}