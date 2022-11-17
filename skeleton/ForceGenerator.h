#pragma once

#include "Particle.h"
#include <list>
#include <random>

class ForceGenerator 
{
public:
	virtual void updateForce(Particle* particle, double duration) = 0;
	string _name;
	double t = -1e10; // If starting negative --> eternal
};