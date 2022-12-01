#pragma once

#include "ForceGenerator.h"

#include <map>

typedef pair<ForceGenerator*, Particle*> FRPair;

/// <summary>
/// Una misma clave -generador- puede tener mas de un valor -particula-
/// </summary>
/// <param name="multimap"></param>
class ParticleForceRegistry : public multimap<ForceGenerator*, Particle*> 
{
public:
	void updateForces(double duration) 
	{
		for (auto it = begin(); it != end(); it++) 
		{
			it->first->updateForce(it->second, duration);
		}
	}

	void addRegistry(ForceGenerator* fg, Particle* p) { insert({ fg, p }); }

	void deleteRegistry(ForceGenerator* fg) { erase(fg); }

	void deleteParticleRegistry(Particle* p) 
	{  
		for (auto it = begin(); it != end(); it++) 
		{
			if (it->second == p) it = erase(it);
		}
	}
};