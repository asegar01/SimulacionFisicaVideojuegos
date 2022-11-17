#include "GravityForceGenerator.h"

void GravityForceGenerator::updateForce(Particle* particle, double t) 
{
	// Check that the particle has Finite Mass
	if (fabs(particle->getInverseMass()) < 1e-10) return;

	// Apply the mass scaled gravity
	particle->addForce(_gravity * particle->getMass());
}