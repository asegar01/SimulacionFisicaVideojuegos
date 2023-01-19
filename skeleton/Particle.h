#pragma once

#include "RenderUtils.hpp"
#include "core.hpp"

#include <memory>
#include <chrono>
#include <string>
#include <list>
#include <cmath>

using namespace physx;
using namespace std;

enum ParticleType 
{
	SPHERE, BOX, CAPSULE, FIREWORK, WATER, UNUSED
};

class Particle
{
public:
	Particle(ParticleType type, Vector3 pos, Vector3 vel, Vector3 acc, float mass, float damping, double time);
	~Particle() { renderItem->release(); };

	virtual void integrate(double t);
	virtual Particle* clone() const;

	void setPosition(Vector3 pos) { _pos.p = pos; }
	void setVelocity(Vector3 vel) { _vel = vel; }

	Vector3 getPosition() { return _pos.p; }
	float getInverseMass() { return 1 / _mass; }
	double getRemainingTime() { return _time; }
	ParticleType getType() { return _type; }

protected:
	RenderItem* renderItem;
	ParticleType _type;
	PxTransform _pos;
	Vector3 _vel;
	Vector3 _acc;
	float _mass;
	float _damping;
	double _time;
	double _r, _g, _b;
};

