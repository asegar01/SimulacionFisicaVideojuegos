#include "WorldManager.h"

#include "SolidGenerator.h"
#include "GaussianSolidGenerator.h"
#include "RigidBody.h"

void WorldManager::createScene() 
{
	// Plane as a solid rigid
	PxRigidStatic* floor = _gPhysics->createRigidStatic(PxTransform({ 0.0, 0.0, 0.0 }));
	PxShape* shape = CreateShape(PxBoxGeometry(100, 0.1, 100));
	floor->attachShape(*shape);
	auto itemFloor = new RenderItem(shape, floor, { 0.8, 0.8, 0.8, 1.0 });
	_gScene->addActor(*floor);

	// Add walls
	PxRigidStatic* wall = _gPhysics->createRigidStatic(PxTransform({ 10.0, 10.0, -30.0 }));
	shape = CreateShape(PxBoxGeometry(40, 20, 1));
	wall->attachShape(*shape);
	auto itemWall = new RenderItem(shape, wall, { 0.8, 0.8, 0.8, 1.0 });
	_gScene->addActor(*wall);

	wall = _gPhysics->createRigidStatic(PxTransform({ 10.0, 10.0, 50.0 }));
	shape = CreateShape(PxBoxGeometry(40, 20, 1));
	wall->attachShape(*shape);
	itemWall = new RenderItem(shape, wall, { 0.8, 0.8, 0.8, 1.0 });
	_gScene->addActor(*wall);

	wall = _gPhysics->createRigidStatic(PxTransform({ -30.0, 10.0, 10.0 }));
	shape = CreateShape(PxBoxGeometry(1, 20, 40));
	wall->attachShape(*shape);
	itemWall = new RenderItem(shape, wall, { 0.8, 0.8, 0.8, 1.0 });
	_gScene->addActor(*wall);

	wall = _gPhysics->createRigidStatic(PxTransform({ 50.0, 10.0, 10.0 }));
	shape = CreateShape(PxBoxGeometry(1, 20, 40));
	wall->attachShape(*shape);
	itemWall = new RenderItem(shape, wall, { 0.8, 0.8, 0.8, 1.0 });
	_gScene->addActor(*wall);

	_solid_generators.push_back(new GaussianSolidGenerator("Rigidbody", { 5.0, -10.0, 5.0 }, new RigidBody(RBBOX, { 0.0, 50.0, 0.0 },
		{ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.5, 0.5, 0.5 }, 10, _gPhysics), { 10.0, 10.0, 10.0 }, { 5.0, 5.0, 5.0 }, _gPhysics, this));
}

void WorldManager::update(double t) 
{
	_time_gen -= t;

	if (_solid_generators.size() != 0 && _time_gen < 0) 
	{
		for (auto g : _solid_generators) 
		{
			if (_solids.size() < _num_solids) 
			{
				auto l = (g)->generateSolids();
				_solids.push_back(l);
				_gScene->addActor(*l);
			}
		}

		_time_gen = 2.0;
	}

	sFR.get()->updateForces(t);

	if (explode) eFG->addTime(t);
}

void WorldManager::increase() 
{
	if (springActive)
		aSFG->setK(aSFG->getK() + 1.0);

	if (buoyancyActive)
		bFG->setVolume(bFG->getVolume() + 100.0f);
}

void WorldManager::decrease() 
{
	if (springActive && aSFG->getK() > 1.0)
		aSFG->setK(aSFG->getK() - 1.0);

	if (buoyancyActive && bFG->getVolume() > 100.0f)
		bFG->setVolume(bFG->getVolume() - 100.0f);
}

void WorldManager::generateWind()
{
	WindGenerator* whS = new WindGenerator({ -100.0, 50.0, 0.0 }, 2.0, 0.0, 100.0, 100.0, 100.0);
	sFR.get()->addRegistry(whS, springSolid);
}

void WorldManager::generateWhirlwind() 
{
	PxRigidDynamic* solid = _gPhysics->createRigidDynamic(PxTransform({ 0.0, 20.0, 0.0 }));
	PxMaterial* material = _gPhysics->createMaterial(0.5, 0.5, 0.5); // creacion del material
	PxShape* shape = PxRigidActorExt::createExclusiveShape(*solid, PxSphereGeometry(1.0), *material);
	PxRigidBodyExt::updateMassAndInertia(*solid, 10); // Densidad del solido (calcula la masa y el tensor de inercia)
	solid->setLinearVelocity({ 0.0, 0.0, 0.0 });
	solid->setAngularVelocity({ 0.0, 0.0, 0.0 });
	solid->setLinearDamping(0.15);
	auto itemSolid = new RenderItem(shape, solid, { 0.13, 0.7, 0.67, 1.0 });
	_solids.push_back(solid);
	_gScene->addActor(*solid);

	// Aplicar un torque al cuerpo rígido
	Vector3 torque(0.0, 10.0, 0.0);
	solid->addTorque(torque);

	WhirlwindGenerator* whFG = new WhirlwindGenerator({ 5.0, 0.0, 5.0 }, 1.0, 2.0);
	sFR.get()->addRegistry(whFG, solid);
}

void WorldManager::generateExplosion()
{
	explode = true;

	eFG = new ExplosionGenerator({ 0.0, 0.0, 0.0 }, 1e4, 1000.0);
	for (auto s : _solids)
		sFR.get()->addRegistry(eFG, s);
}

void WorldManager::generateSpring()
{
	springSolid = _gPhysics->createRigidDynamic(PxTransform({ 0.0, 50.0, 0.0 }));
	PxMaterial* material = _gPhysics->createMaterial(0.5, 0.5, 0.5); // creacion del material
	PxShape* shape = PxRigidActorExt::createExclusiveShape(*springSolid, PxSphereGeometry(1.0), *material);
	PxRigidBodyExt::updateMassAndInertia(*springSolid, 10); // Densidad del solido (calcula la masa y el tensor de inercia)
	springSolid->setLinearVelocity({ 0.0, 0.0, 0.0 });
	springSolid->setAngularVelocity({ 0.0, 0.0, 0.0 });
	springSolid->setLinearDamping(0.15);
	auto itemSolid = new RenderItem(shape, springSolid, { 0.13, 0.7, 0.67, 1.0 });
	_solids.push_back(springSolid);
	_gScene->addActor(*springSolid);

	// Aplicar un torque al cuerpo rígido
	Vector3 torque(0.0, 10.0, 0.0);
	springSolid->addTorque(torque);

	aSFG = new AnchoredSpringFG(20, 5, { 0.0, 60.0, 0.0 });
	sFR.get()->addRegistry(aSFG, springSolid);

	springActive = !springActive;
}

void WorldManager::generateBuoyancy()
{
	buoyancySolid = _gPhysics->createRigidDynamic(PxTransform({ 0.0, 50.0, 0.0 }));
	PxMaterial* material = _gPhysics->createMaterial(0.5, 0.5, 0.5); // creacion del material
	PxShape* shape = PxRigidActorExt::createExclusiveShape(*buoyancySolid, PxSphereGeometry(1.0), *material);
	PxRigidBodyExt::updateMassAndInertia(*buoyancySolid, 10); // Densidad del solido (calcula la masa y el tensor de inercia)
	buoyancySolid->setLinearVelocity({ 0.0, 0.0, 0.0 });
	buoyancySolid->setAngularVelocity({ 0.0, 0.0, 0.0 });
	buoyancySolid->setLinearDamping(0.15);
	auto itemSolid = new RenderItem(shape, buoyancySolid, { 0.13, 0.7, 0.67, 1.0 });
	_solids.push_back(buoyancySolid);
	_gScene->addActor(*buoyancySolid);

	// Agua
	bFG = new BuoyancyForceGenerator(1.0, 10.0, 10.0);
	sFR.get()->addRegistry(bFG, buoyancySolid);

	// Aceite
	/*bFG = new BuoyancyForceGenerator(1.0, 10.0, 0.1);
	sFR.get()->addRegistry(bFG, solid);*/

	buoyancyActive = !buoyancyActive;
}
