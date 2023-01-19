#pragma once

#include "Particle.h"
#include "ParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "Firework.h"

class ParticleSystem
{
public:
	ParticleSystem() : _particles(0) {};
	~ParticleSystem() {};

	void update(double t);

	// Devuelve el generador de particulas especifico
	ParticleGenerator* getParticleGenerator(string name);

	// Genera un sistema de fuegos artificiales
	void generateFirework();

	void shootFirework(int type);

	// Una vez el tiempo de vida de la particula llega a cero
	void onParticleDeath(Particle* p);

protected:
	list<Particle*> _particles;
	list<ParticleGenerator*> _particleGenerators;

	vector<Firework*> _fireworksPool;
	ParticleGenerator* _fireworkGenerator;
};

