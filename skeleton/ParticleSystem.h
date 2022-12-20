#pragma once

#include "Projectile.h"
#include "Particle.h"
#include "ParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "Firework.h"
#include "ParticleForceRegistry.h"
#include "GravityForceGenerator.h"
#include "WindGenerator.h"
#include "WhirlwindGenerator.h"
#include "ExplosionGenerator.h"
#include "SpringForceGenerator.h"
#include "AnchoredSpringFG.h"
#include "BuoyancyForceGenerator.h"
#include "GaussianSolidGenerator.h"
#include "WorldManager.h"

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

	void update(double t);

	// Devuelve el generador de particulas especifico
	ParticleGenerator* getParticleGenerator(string name);

	// Genera un sistema de fuego artificiales
	void generateFireworkSystem();

	void shootFirework(int type);

	void onParticleDeath(Particle*);

	// Gravedad
	void addGravityParticles();

	// Viento
	void addWindParticles();

	// Torbellino
	void addWhirlwindParticles();

	// Explosion
	void addExplosionParticles();

	// Muelle
	void generateSpringDemo();
	void increase();
	void decrease();
	void generateWindSpringDemo();

	// Slinky
	void generateSlinky();

	// Flotabilidad
	void generateBuoyancy();
	inline void increaseMass() { buoyancyParticle->setMass(buoyancyParticle->getMass() + 1.0f); }
	inline void decreaseMass() { if (buoyancyParticle->getMass() > 1.0f) buoyancyParticle->setMass(buoyancyParticle->getMass() - 1.0f); }

protected:
	list<Particle*> _particles;
	list<ParticleGenerator*> _particle_generators;
	list<SolidGenerator*> _solid_generators;

	vector<Firework*> _fireworks_pool;
	ParticleGenerator* _firework_gen;

	unique_ptr<ParticleForceRegistry> pFR;
	list<ForceGenerator*> _force_generators;

	// Explosion
	ExplosionGenerator* eFG = nullptr;
	bool explode = false;

	// Muelle
	Particle* springParticle = nullptr;
	AnchoredSpringFG* aSFG = nullptr;

	// Flotabilidad
	Particle* buoyancyParticle = nullptr;
	BuoyancyForceGenerator* bFG = nullptr;

	bool springActive = false;
	bool buoyancyActive = false;

	WorldManager* worldManager = nullptr;
};