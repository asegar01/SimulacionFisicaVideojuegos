#include "Projectile.h"

Projectile::Projectile(TYPE currentShotType) : Particle(GetCamera()->getEye(), GetCamera()->getDir())
{
	switch (currentShotType)
	{
	case PISTOL:
		setMass(2.0f); // 2.0 Kg
		setVelocity(Vector3(0.0f, 0.0f, 35.0f)); // 35 m/s
		setAcceleration(Vector3(0.0f, -1.0f, 0.0f));
		setDamping(0.99f);
		break;
	case ARTILLERY:
		setMass(200.0f); // 200.0 Kg
		setVelocity(Vector3(0.0f, 30.0f, 40.0f));
		setAcceleration(Vector3(0.0f, -20.0f, 0.0f));
		setDamping(0.99f);
		break;
	case FIREBALL:
		setMass(1.0f); // 1.0 Kg
		setVelocity(Vector3(0.0f, 0.0f, 10.0f));
		setAcceleration(Vector3(0.0f, 0.6f, 0.0f)); // floats
		setDamping(0.9f);
		break;
	case LASER:
		setMass(0.1f); // almost no weight
		setVelocity(Vector3(0.0f, 0.0f, 100.0f)); // No gravity
		setAcceleration(Vector3(0.0f, 0.0f, 0.0f));
		setDamping(0.99f);
		break;
	}

	//shot->startTime = GetLastFrame();
	//shot->type = currentShotType;
}