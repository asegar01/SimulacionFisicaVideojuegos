#include "WhirlwindGenerator.h"

void WhirlwindGenerator::updateForce(Particle* particle, double t) 
{
	// Check that the particle has Finite Mass
	if (fabs(particle->getInverseMass()) < 1e-10) return;

	auto const pos = particle->getPosition().p;

	// Compute the whirlwind force
	Vector3 v = particle->getVel() - K * Vector3(-(pos.z - _origin.z), 50 - (pos.y - _origin.y), (pos.x - _origin.x));
	float drag_coef = v.normalize();
	Vector3 whirlwindF;
	drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;
	whirlwindF = -v * drag_coef;

	// Apply the whirlwind force
	cout << whirlwindF.x << "\t" << whirlwindF.y << "\t" << whirlwindF.z << endl;
	particle->addForce(whirlwindF);
}

void WhirlwindGenerator::updateForceRB(PxRigidDynamic* solid, double t) 
{
	// Check that the particle has Finite Mass
	if (fabs(solid->getInvMass()) < 1e-10) return;

	auto const pos = solid->getGlobalPose().p;

	// Compute the whirlwind force
	Vector3 v = solid->getLinearVelocity() - K * Vector3(-(pos.z - _origin.z), 50 - (pos.y - _origin.y), (pos.x - _origin.x));
	float drag_coef = v.normalize();
	Vector3 whirlwindF;
	drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;
	whirlwindF = -v * drag_coef;

	// Apply the whirlwind force
	cout << whirlwindF.x << "\t" << whirlwindF.y << "\t" << whirlwindF.z << endl;
	solid->addForce(whirlwindF);
}