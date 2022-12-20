#include "BuoyancyForceGenerator.h"

void BuoyancyForceGenerator::updateForce(Particle* particle, double t) 
{
	// Check that the particle has Finite Mass
	if (fabs(particle->getInverseMass()) < 1e-10) return;

	// Compute the buoyancy force
	const float h = particle->getPosition().p.y;
	const float h0 = _liquid_particle->getPosition().p.y;
	Vector3 f(0, 0, 0);

	float immersed = 0.0;
	if (h - h0 > _height * 0.5) immersed = 0.0;
	else if (h0 - h > _height * 0.5) immersed = 1.0; // Totally immersed
	else immersed = (h0 - h) / _height + 0.5;

	f.y = _liquid_density * _volume * immersed * _gravity;

	// Apply the buoyancy force
	particle->addForce(f);
}

void BuoyancyForceGenerator::updateForceRB(PxRigidDynamic* solid, double t) 
{
	// Check that the particle has Finite Mass
	if (fabs(solid->getInvMass()) < 1e-10) return;

	// Compute the buoyancy force
	const float h = solid->getGlobalPose().p.y;
	const float h0 = _liquid_particle->getPosition().p.y;
	Vector3 f(0, 0, 0);

	float immersed = 0.0;
	if (h - h0 > _height * 0.5) immersed = 0.0;
	else if (h0 - h > _height * 0.5) immersed = 1.0; // Totally immersed
	else immersed = (h0 - h) / _height + 0.5;

	f.y = _liquid_density * _volume * immersed * _gravity;

	// Apply the buoyancy force
	solid->addForce(f);
}