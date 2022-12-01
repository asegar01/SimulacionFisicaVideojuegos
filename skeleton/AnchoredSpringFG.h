#pragma once

#include "core.hpp"
#include "SpringForceGenerator.h"

class AnchoredSpringFG : public SpringForceGenerator 
{
public:
	AnchoredSpringFG(double k, double resting, const Vector3& anchor_pos) : SpringForceGenerator(k, resting, nullptr) 
	{ _other = new Particle(BOX, anchor_pos, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, 0.0f, 0.0f, 1e6); }
	~AnchoredSpringFG() { delete _other; };
};
