#pragma once

#include <iostream>
#include <list>
#include <random>

#include "core.hpp"
#include "Particle.h"

class ForceGenerator 
{
public:
	virtual void updateForce(Particle* particle, double duration) = 0;
	string _name;
	double t = -1e10; // If starting negative --> eternal
};