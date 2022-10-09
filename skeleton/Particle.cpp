#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel) : pose(Pos), vel(Vel)
{
	renderItem = std::make_unique<RenderItem>(CreateShape(PxSphereGeometry(1)), &pose, Vector4(1.0, 0.0, 1.0, 1.0));
}

Particle::~Particle()
{
	renderItem.release();
	renderItem = nullptr;
}

void Particle::integrate(double t)
{
	// Trivial case, infinite mass --> do nothing
	//if (inverse_mass <= 0.0f) return;

	// Update position
	pose.p += vel * t;

	// Update linear velocity
	//vel += a * t;

	// Impose drag (damping)
	//vel *= powf(damping, t);
}