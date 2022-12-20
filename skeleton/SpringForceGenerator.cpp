#include "SpringForceGenerator.h"

void SpringForceGenerator::updateForce(Particle* particle, double t) 
{
	// Check that the particle has Finite Mass
	if (fabs(particle->getInverseMass()) < 1e-10) return;

	// Particle is the particle to apply the force
	Vector3 force = _other->getPosition().p - particle->getPosition().p;

	const float length = force.normalize();
	const float delta_x = length - _resting_length;

	force *= delta_x * _k;

	// Apply the spring force
	particle->addForce(force);
}

void SpringForceGenerator::updateForceRB(PxRigidDynamic* solid, double t) 
{
	// Check that the particle has Finite Mass
	if (fabs(solid->getInvMass()) < 1e-10) return;

	// Solid is the rigidbody to apply the force
	Vector3 force = _other->getPosition().p - solid->getGlobalPose().p;

	const float length = force.normalize();
	const float delta_x = length - _resting_length;

	force *= delta_x * _k;

	// Apply the spring force
	solid->addForce(force);
}