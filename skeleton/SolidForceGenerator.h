#pragma once

#include <iostream>
#include <list>
#include <random>
#include <cmath>

#include "core.hpp"
#include "PxRigidDynamic.h"

using namespace physx;
using namespace std;

class SolidForceGenerator 
{
public:
	virtual void updateForceRB(PxRigidDynamic* solid, double duration) = 0;
	string _name;
	double t = -1e10; // If starting negative --> eternal
};