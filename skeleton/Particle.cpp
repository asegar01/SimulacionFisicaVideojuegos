#include "Particle.h"

Particle::Particle(ParticleType type, Vector3 pos, Vector3 vel, Vector3 acc, float mass, float damping, double time)
	: _type(type), _pos(pos), _vel(vel), _acc(acc), _mass(mass), _damping(damping), _time(time) 
{
	switch (_type)
	{
	case SPHERE: renderItem = new RenderItem(CreateShape(PxSphereGeometry(_mass)), &_pos, Vector4(1.0, 0.0, 1.0, 1.0)); break;
	case BOX: renderItem = new RenderItem(CreateShape(PxBoxGeometry(_mass, _mass, _mass)), &_pos, Vector4(1.0, 1.0, 0.0, 1.0)); break;
	case CAPSULE: renderItem = new RenderItem(CreateShape(PxCapsuleGeometry(_mass, _mass)), &_pos, Vector4(0.0, 1.0, 1.0, 1.0)); break;
	case FIREWORK: renderItem = new RenderItem(CreateShape(PxSphereGeometry(_mass)), &_pos, Vector4(1.0, 0.0, 0.0, 1.0)); break;
	case WATER: renderItem = new RenderItem(CreateShape(PxBoxGeometry(10.0, 1.0, 7.5)), &_pos, Vector4(0.0, 0.0, 0.5, 1.0)); break;
	case UNUSED: break;
	default: break;
	}
}

void Particle::integrate(double t) 
{
	// Trivial case, infinite mass --> do nothing
	if (getInverseMass() <= 0.0f) return;

	// Update position
	_pos.p += _vel * t;

	// Update linear velocity
	_vel += _acc * t;

	// Impose drag (damping)
	_vel *= powf(_damping, t);

	// Actualiza el tiempo de vida restante de la particula
	_time -= t;
}

Particle* Particle::clone() const
{
	Particle* p = new Particle(FIREWORK, _pos.p, _vel, _acc, _mass, _damping, _time);
	return p;
}