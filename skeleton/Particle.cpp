#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel) : pose(Pos), _vel(Vel), _remaining_time(5)
{
	//renderItem = new RenderItem(CreateShape(PxSphereGeometry(1)), &pose, Vector4(1.0, 0.0, 1.0, 1.0));
	//renderItem = new RenderItem(CreateShape(PxSphereGeometry(1)), &pose, Vector4(1.0, 0.0, 1.0, 1.0));
}

Particle::Particle(ParticleType type, Vector3 Pos, Vector3 Vel, Vector3 Acc, float Damping) : pose(Pos), _vel(Vel), _accel(Acc), damping(Damping), _remaining_time(5), _type(type)
{
	switch (_type)
	{
	case SPHERE: renderItem = new RenderItem(CreateShape(PxSphereGeometry(1)), &pose, Vector4(1.0, 0.0, 1.0, 1.0)); break;
	case BOX: renderItem = new RenderItem(CreateShape(PxBoxGeometry(1, 1, 1)), &pose, Vector4(1.0, 1.0, 0.0, 1.0)); break;
	case CAPSULE: renderItem = new RenderItem(CreateShape(PxCapsuleGeometry(1, 1)), &pose, Vector4(0.0, 1.0, 1.0, 1.0)); break;
	default: break;
	}
}

void Particle::integrate(double t)
{
	// Trivial case, infinite mass --> do nothing
	//if (inverse_mass <= 0.0f) return;

	// Update position
	pose.p += _vel * t;

	// Update linear velocity
	_vel += _accel * t;

	// Impose drag (damping)
	_vel *= powf(damping, t);

	// Actualiza el tiempo de vida restante de la particula
	_remaining_time -= t;
}

Particle* Particle::clone() const
{
	Particle* p = new Particle(SPHERE, pose.p, _vel, _accel, damping);
	return p;
}