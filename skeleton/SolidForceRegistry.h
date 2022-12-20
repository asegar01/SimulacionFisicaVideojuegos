#pragma once

#include "SolidForceGenerator.h"

#include <map>

/// <summary>
/// Una misma clave -generador- puede tener mas de un valor -rigidbody-
/// </summary>
/// <param name="multimap"></param>
class SolidForceRegistry : public multimap<SolidForceGenerator*, PxRigidDynamic*> 
{
public:
	void updateForces(double duration) 
	{
		for (auto it = begin(); it != end(); ++it) 
		{
			it->first->updateForceRB(it->second, duration);
		}
	}

	void addRegistry(SolidForceGenerator* sFG, PxRigidDynamic* rB) { insert({ sFG, rB }); }

	void deleteRegistry(SolidForceGenerator* sFG) { erase(sFG); }

	void deleteSolidRegistry(PxRigidDynamic* rB) 
	{
		for (auto it = begin(); it != end(); ++it) 
		{
			if (it->second == rB) it = erase(it);
		}
	}
};