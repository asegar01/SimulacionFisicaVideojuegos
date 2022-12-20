#pragma once

#include <iostream>
#include <list>
#include <random>

#include "core.hpp"
#include "RigidBody.h"

class SolidForceGenerator 
{
public:
	virtual void updateForceRB(PxRigidDynamic* solid, double duration) = 0;
	string _name;
	double t = -1e10; // If starting negative --> eternal
};