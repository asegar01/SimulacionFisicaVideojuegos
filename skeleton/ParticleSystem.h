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

protected:
	list<Particle*> _particles;
	list<ParticleGenerator*> _particle_generators;

	vector<Firework*> _fireworks_pool;
	ParticleGenerator* _firework_gen;

	unique_ptr<ParticleForceRegistry> pFR;
};