#include "WindGenerator.h"

void WindGenerator::updateForce(Particle* particle, double t) 
{
	// Check that the particle has Finite Mass
	if (fabs(particle->getInverseMass()) < 1e-10) return;

	// Check that the particle is inside action volume
	auto const pos = particle->getPosition().p;
	if (pos.x < -_x || pos.x > _x || pos.y < -_y || pos.y > _y || pos.z < -_z || pos.z > _z) return;

	// Compute the wind force
	Vector3 v = particle->getVel() - _vel;
	float drag_coef = v.normalize();
	Vector3 windF;
	drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;
	windF = -v * drag_coef;

	// Apply the wind force
	cout << windF.x << "\t" << windF.y << "\t" << windF.z << endl;
	particle->addForce(windF);
}