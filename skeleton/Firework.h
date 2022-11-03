#pragma once

#include "RenderUtils.hpp"
#include "core.hpp"

#include "Particle.h"

class Firework
{
public:
	Firework() {};
	~Firework();

	int integrate(double t);

	virtual Particle* clone() const;

	list<Particle*> explode();

protected:
	list<shared_ptr<Particle>> _gens;
};
