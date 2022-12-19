#include "WorldManager.h"

#include "SolidGenerator.h"
#include "GaussianSolidGenerator.h"
#include "RigidBody.h"

WorldManager::WorldManager(PxScene* gScene, PxPhysics* gPhysics) : _gScene(gScene), _gPhysics(gPhysics)
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
		{ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.5, 0.5, 0.5 }, 10, _gPhysics), {10.0, 10.0, 10.0}, {5.0, 5.0, 5.0}, _gPhysics, this));
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
}
