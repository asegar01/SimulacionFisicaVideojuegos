#include "BuoyancyGenerator.h"

void BuoyancyGenerator::updateForceRB(PxRigidDynamic* solid, double t)
{
	// Check that the solid has Finite Mass
	if (fabs(solid->getInvMass()) < 1e-10) return;

	// Check that the solid is inside action volume
	auto const pos = solid->getGlobalPose().p;

	if (pos.x < _pos.x - _offset || pos.x > _pos.x + _offset || 
		pos.z < _pos.z - 3 * _offset / 4 || pos.z > _pos.z + 3 * _offset / 4) return;

	// Compute the buoyancy force
	const float h = solid->getGlobalPose().p.y;
	const float h0 = _liquidParticle->getPosition().y;
	Vector3 f = { 0.0, 0.0, 0.0 };

	float immersed = 0.0;
	if (h - h0 > _height * 0.5) immersed = 0.0;
	else if (h0 - h > _height * 0.5) immersed = 1.0;
	else immersed = (h0 - h) / _height + 0.5;

	f.y = _liquidDensity * _volume * immersed * _gravity;

	// Apply the buoyancy force
	cout << f.x << "\t" << f.y << "\t" << f.z << endl;
	solid->addForce(f);
}