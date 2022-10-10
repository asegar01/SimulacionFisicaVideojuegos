#pragma once

#include "RenderUtils.hpp"
#include "core.hpp"
#include "Particle.h"

#include <memory>

using namespace physx;

class Projectile : public Particle
{
public:
	enum TYPE { PISTOL, ARTILLERY, FIREBALL, LASER, UNUSED };

	Projectile(TYPE type);
};