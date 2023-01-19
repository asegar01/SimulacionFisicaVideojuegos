#include "ExplosionGenerator.h"

void ExplosionGenerator::updateForceRB(PxRigidDynamic* solid, double t)
{
	// Check that the solid has Finite Mass
	if (fabs(solid->getInvMass()) < 1e-10 || _timeLeft < 0) return;

	auto const pos = solid->getGlobalPose().p;

	// Compute the explosion force
	auto const r = sqrt(pow((pos.x - _origin.x), 2) + pow((pos.y - _origin.y), 2) + pow((pos.z - _origin.z), 2));
	Vector3 force = { 0.0, 0.0, 0.0 };

	if (r < _r)
	{
		auto const k1 = _r / pow(r, 2);
		auto const k2 = exp(-(t / _time));

		force = Vector3(pos.x - _origin.x, pos.y - _origin.y, pos.z - _origin.z) * k1 * k2;
	}

	Vector3 v = solid->getLinearVelocity() - force;
	float drag_coef = v.normalize();
	Vector3 explosionF;
	drag_coef = _k * drag_coef + _k * drag_coef * drag_coef;
	explosionF = -v * drag_coef;

	// Apply the explosion force
	cout << explosionF.x << "\t" << explosionF.y << "\t" << explosionF.z << endl;
	solid->addForce(explosionF);

	// Actualiza el tiempo restante
	_timeLeft -= t;
}
