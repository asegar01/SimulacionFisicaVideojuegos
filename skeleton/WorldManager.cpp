#include "WorldManager.h"

#include "PxPhysicsAPI.h"
#include "PxPhysics.h"
#include "PxScene.h"

void WorldManager::createWorldScene() 
{
	// Suelo
	PxRigidStatic* floor = _gPhysics->createRigidStatic(PxTransform(20.0f, 0.0f, -39.0f));
	PxMaterial* material = _gPhysics->createMaterial(0.5, 0.5, 0.3);
	PxShape* shape = PxRigidActorExt::createExclusiveShape(*floor, PxBoxGeometry(70.0, 1.0, 10.0), *material);
	auto itemFloor = new RenderItem(shape, floor, { 0.0, 0.42, 0.24, 1.0 });
	_gScene->addActor(*floor);

	// Paredes
	PxRigidStatic* wall = _gPhysics->createRigidStatic(PxTransform({ 20.0, 0.0, -29.0 }));
	shape = CreateShape(PxBoxGeometry(69, 2, 1));
	wall->attachShape(*shape);
	auto itemWall = new RenderItem(shape, wall, { 0.2, 0.2, 0.2, 1.0 });
	_gScene->addActor(*wall);

	wall = _gPhysics->createRigidStatic(PxTransform({ -50.0, 0.0, -39.0 }));
	shape = CreateShape(PxBoxGeometry(1, 2, 11));
	wall->attachShape(*shape);
	itemWall = new RenderItem(shape, wall, { 0.2, 0.2, 0.2, 1.0 });
	_gScene->addActor(*wall);

	wall = _gPhysics->createRigidStatic(PxTransform({ 90.0, 0.0, -39.0 }));
	wall->attachShape(*shape);
	itemWall = new RenderItem(shape, wall, { 0.2, 0.2, 0.2, 1.0 });
	_gScene->addActor(*wall);

	wall = _gPhysics->createRigidStatic(PxTransform({ -20.0, 0.0, -49.0 }));
	shape = CreateShape(PxBoxGeometry(11, 2, 1));
	wall->attachShape(*shape);
	itemWall = new RenderItem(shape, wall, { 0.2, 0.2, 0.2, 1.0 });
	_gScene->addActor(*wall);

	wall = _gPhysics->createRigidStatic(PxTransform({ 20.0, 0.0, -49.0 }));
	wall->attachShape(*shape);
	itemWall = new RenderItem(shape, wall, { 0.2, 0.2, 0.2, 1.0 });
	_gScene->addActor(*wall);

	wall = _gPhysics->createRigidStatic(PxTransform({ 60.0, 0.0, -49.0 }));
	wall->attachShape(*shape);
	itemWall = new RenderItem(shape, wall, { 0.2, 0.2, 0.2, 1.0 });
	_gScene->addActor(*wall);

	// Meta
	goalUpper = _gPhysics->createRigidStatic(PxTransform({ 0.0f, 0.0f, 0.0f }));
	shape = PxRigidActorExt::createExclusiveShape(*goalUpper, PxBoxGeometry(1.0f, 1.0f, 0.2f), *material);
	auto itemGoal = new RenderItem(shape, goalUpper, { 0.1, 0.0, 0.0, 1.0 });
	_gScene->addActor(*goalUpper);

	goalLower = _gPhysics->createRigidStatic(PxTransform({ 0.0f, 0.0f, 0.0f }));
	goalLower->setName("goal");
	shape = PxRigidActorExt::createExclusiveShape(*goalLower, PxBoxGeometry(0.2f, 5.0f, 0.2f), *material);
	itemGoal = new RenderItem(shape, goalLower, { 0.9, 0.9, 0.9, 1.0 });
	_gScene->addActor(*goalLower);

	// Pelota
	ball = _gPhysics->createRigidDynamic(PxTransform({ -40.0, 20.0, -40.0 }));
	ball->setName("ball");
	material = _gPhysics->createMaterial(0.5, 0.5, 0.5);
	shape = PxRigidActorExt::createExclusiveShape(*ball, PxSphereGeometry(0.75), *material);
	PxRigidBodyExt::updateMassAndInertia(*ball, 10); // Densidad del solido (calcula la masa y el tensor de inercia)
	ball->setLinearVelocity({ 0.0, 0.0, 0.0 });
	ball->setAngularVelocity({ 0.0, 0.0, 0.0 });
	ball->setLinearDamping(0.4);
	auto itemSolid = new RenderItem(shape, ball, { 1.0, 1.0, 1.0, 1.0 });
	_gScene->addActor(*ball);

	// Siguiente escena
	nextScene();
	nextScene();
	nextScene();
	nextScene();
}

void WorldManager::nextScene()
{
	switch (_currentScene)
	{
	case SCENE0: createScene01(); break;
	case SCENE1: createScene02(); break;
	case SCENE2: createScene03(); break;
	case SCENE3: createScene04(); break;
	default: break;
	}
}

void WorldManager::createScene01()
{
	// Plataforma
	createPlatform(-40.0f);

	// Pelota
	setBallStart();

	// Meta
	setGoalStart(-40.0f);

	// Actualiza la escena
	_currentScene = static_cast<CurrentScene>(_currentScene + 1);
}

void WorldManager::createScene02() 
{
	// Plataforma
	createPlatform(0.0f);

	// Molino de viento
	PxRigidDynamic* dyn = _gPhysics->createRigidDynamic(PxTransform({ 0.0f, 7.0f, -100.f }));
	PxMaterial* material = _gPhysics->createMaterial(0.5, 0.5, 0.3);
	auto shape1 = PxRigidActorExt::createExclusiveShape(*dyn, PxBoxGeometry(6.0f, 0.6f, 0.1f), *material);
	auto shape2 = PxRigidActorExt::createExclusiveShape(*dyn, PxBoxGeometry(0.6f, 6.0f, 0.1f), *material);
	dyn->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
	dyn->setAngularVelocity({ 0.0f, 0.0f, 2.0f });
	dyn->setAngularDamping(0.0f);
	dyn->setMass(0.0f);
	dyn->setMassSpaceInertiaTensor({ 0.0f, 0.0f, 0.0f });
	auto itemWindmill = new RenderItem(shape1, dyn, { 1.0, 1.0, 1.0, 1.0 });
	itemWindmill = new RenderItem(shape2, dyn, { 1.0, 1.0, 1.0, 1.0 });
	_gScene->addActor(*dyn);

	PxRigidStatic* st = _gPhysics->createRigidStatic(PxTransform({ -2.0f, 3.0f, -102.0f }));
	auto shape3 = PxRigidActorExt::createExclusiveShape(*st, PxBoxGeometry(1.0f, 3.0f, 1.6f), *material);
	itemWindmill = new RenderItem(shape3, st, { 1.0, 1.0, 1.0, 1.0 });
	_gScene->addActor(*st);

	PxRigidStatic* st2 = _gPhysics->createRigidStatic(PxTransform({ 2.0f, 3.0f, -102.0f }));
	shape3 = PxRigidActorExt::createExclusiveShape(*st2, PxBoxGeometry(1.0f, 3.0f, 1.6f), *material);
	itemWindmill = new RenderItem(shape3, st2, { 1.0, 1.0, 1.0, 1.0 });
	_gScene->addActor(*st2);

	PxRigidStatic* st3 = _gPhysics->createRigidStatic(PxTransform({ 0.0f, 6.0f, -102.0f }));
	shape3 = PxRigidActorExt::createExclusiveShape(*st3, PxBoxGeometry(1.0f, 3.0f, 1.6f), *material);
	itemWindmill = new RenderItem(shape3, st3, { 1.0, 1.0, 1.0, 1.0 });
	_gScene->addActor(*st3);

	// Fuerza de viento
	WindGenerator* wSFG = new WindGenerator({ 0.0, 0.0, 60.0 }, 2.0, 0.0, 10.0, 5.0, 20.0, -80.0);
	sFR->addRegistry(wSFG, ball);

	// Pelota
	setBallStart();

	// Meta
	setGoalStart(0.0f);

	// Actualiza la escena
	_currentScene = static_cast<CurrentScene>(_currentScene + 1);
}

void WorldManager::createScene03()
{
	// Suelo
	PxRigidStatic* floor = _gPhysics->createRigidStatic(PxTransform({ 40.0f, 0.0f, -60.0f }));
	PxMaterial* material = _gPhysics->createMaterial(0.5, 0.5, 0.3);
	PxShape* shape = PxRigidActorExt::createExclusiveShape(*floor, PxBoxGeometry(10.0, 1.0, 10.0), *material);
	auto itemFloor = new RenderItem(shape, floor, { 0.0, 0.42, 0.24, 1.0 });
	_gScene->addActor(*floor);

	floor = _gPhysics->createRigidStatic(PxTransform({ 40.0f, 0.0f, -85.0f }));
	shape = PxRigidActorExt::createExclusiveShape(*floor, PxBoxGeometry(3.0, 1.0, 15.0), *material);
	itemFloor = new RenderItem(shape, floor, { 0.0, 0.42, 0.24, 1.0 });
	_gScene->addActor(*floor);

	floor = _gPhysics->createRigidStatic(PxTransform({ 40.0f, 0.0f, -105.f }));
	shape = PxRigidActorExt::createExclusiveShape(*floor, PxBoxGeometry(10.0, 1.0, 5.0), *material);
	itemFloor = new RenderItem(shape, floor, { 0.0, 0.42, 0.24, 1.0 });
	_gScene->addActor(*floor);

	floor = _gPhysics->createRigidStatic(PxTransform({ 40.0f, 0.0f, -137.5f }));
	shape = PxRigidActorExt::createExclusiveShape(*floor, PxBoxGeometry(10.0, 1.0, 12.5), *material);
	itemFloor = new RenderItem(shape, floor, { 0.0, 0.42, 0.24, 1.0 });
	_gScene->addActor(*floor);

	// Paredes
	PxRigidStatic* wall = _gPhysics->createRigidStatic(PxTransform({ 30.0f, 0.0f, -60.0f }));
	shape = CreateShape(PxBoxGeometry(1, 2, 10));
	wall->attachShape(*shape);
	auto itemWall = new RenderItem(shape, wall, { 0.2, 0.2, 0.2, 1.0 });
	_gScene->addActor(*wall);

	wall = _gPhysics->createRigidStatic(PxTransform({ 50.0f, 0.0f, -60.0f }));
	wall->attachShape(*shape);
	itemWall = new RenderItem(shape, wall, { 0.2, 0.2, 0.2, 1.0 });
	_gScene->addActor(*wall);

	wall = _gPhysics->createRigidStatic(PxTransform({ 30.0f, 0.0f, -125.0f }));
	shape = CreateShape(PxBoxGeometry(1, 2, 25));
	wall->attachShape(*shape);
	itemWall = new RenderItem(shape, wall, { 0.2, 0.2, 0.2, 1.0 });
	_gScene->addActor(*wall);

	wall = _gPhysics->createRigidStatic(PxTransform({ 50.0f, 0.0f, -125.0f }));
	wall->attachShape(*shape);
	itemWall = new RenderItem(shape, wall, { 0.2, 0.2, 0.2, 1.0 });
	_gScene->addActor(*wall);

	wall = _gPhysics->createRigidStatic(PxTransform({ 40.0f, 0.0f, -151.0f }));
	shape = CreateShape(PxBoxGeometry(11, 2, 1));
	wall->attachShape(*shape);
	itemWall = new RenderItem(shape, wall, { 0.2, 0.2, 0.2, 1.0 });
	_gScene->addActor(*wall);

	// Fuerza de flotabilidad
	BuoyancyGenerator* bSFG = new BuoyancyGenerator(0.1f, ball->getMassSpaceInertiaTensor().dot(ball->getMassSpaceInvInertiaTensor()), 
		1000.0f, { 40.0f, 0.0f, -117.5f }, 10.0f);
	sFR->addRegistry(bSFG, ball);

	// Pelota
	setBallStart();

	// Meta
	setGoalStart(40.0f);

	// Actualiza la escena
	_currentScene = static_cast<CurrentScene>(_currentScene + 1);
}

void WorldManager::createScene04()
{
	// Plataforma
	createPlatform(80.0f);

	// Explosivos
	createExplosive(85.0f, -110.0f);
	createExplosive(75.0f, -90.0f);
	createExplosive(82.5f, -70.0f);

	// Pelota
	setBallStart();

	// Meta
	setGoalStart(80.0f);

	// Actualiza la escena
	_currentScene = static_cast<CurrentScene>(_currentScene + 1);
}


void WorldManager::setBallStart()
{
	ball->setGlobalPose(PxTransform({ -40.0, 20.0, -40.0 }));
	ball->setLinearVelocity({ 0.0, 0.0, 0.0 });
	ball->setAngularVelocity({ 0.0, 0.0, 0.0 });
}

void WorldManager::setGoalStart(float x)
{
	goalUpper->setGlobalPose(PxTransform({ x + 0.5f, 8.5f, -134.5f }));
	goalLower->setGlobalPose(PxTransform({ x + 0.0f, 5.0f, -135.0f }));
}

void WorldManager::createPlatform(float x)
{
	// Suelo
	PxRigidStatic* floor = _gPhysics->createRigidStatic(PxTransform({ x + 0.0f, 0.0f, -100.0f }));
	PxMaterial* material = _gPhysics->createMaterial(0.5, 0.5, 0.3);
	PxShape* shape = PxRigidActorExt::createExclusiveShape(*floor, PxBoxGeometry(10.0, 1.0, 50.0), *material);
	auto itemFloor = new RenderItem(shape, floor, { 0.0, 0.42, 0.24, 1.0 });
	_gScene->addActor(*floor);

	// Paredes
	PxRigidStatic* wall = _gPhysics->createRigidStatic(PxTransform({ x + 10.0f, 0.0f, -100.0f }));
	shape = CreateShape(PxBoxGeometry(1, 2, 50));
	wall->attachShape(*shape);
	auto itemWall = new RenderItem(shape, wall, { 0.2, 0.2, 0.2, 1.0 });
	_gScene->addActor(*wall);

	wall = _gPhysics->createRigidStatic(PxTransform({ x - 10.0f, 0.0f, -100.0f }));
	wall->attachShape(*shape);
	itemWall = new RenderItem(shape, wall, { 0.2, 0.2, 0.2, 1.0 });
	_gScene->addActor(*wall);

	wall = _gPhysics->createRigidStatic(PxTransform({ x + 0.0f, 0.0f, -151.0f }));
	shape = CreateShape(PxBoxGeometry(11, 2, 1));
	wall->attachShape(*shape);
	itemWall = new RenderItem(shape, wall, { 0.2, 0.2, 0.2, 1.0 });
	_gScene->addActor(*wall);
}

void WorldManager::createExplosive(float x, float z)
{
	PxRigidStatic* bomb = _gPhysics->createRigidStatic(PxTransform({ x, 1.0f, z }));
	bomb->setName("bomb");
	PxShape* shape1 = CreateShape(PxBoxGeometry(2, 0.5, 2));
	PxShape* shape2 = CreateShape(PxSphereGeometry(1.5));
	bomb->attachShape(*shape1);
	bomb->attachShape(*shape2);
	auto itemWall = new RenderItem(shape1, bomb, { 0.2, 0.2, 0.2, 1.0 });
	itemWall = new RenderItem(shape2, bomb, { 0.5, 0.0, 0.0, 1.0 });
	_gScene->addActor(*bomb);
}

void WorldManager::generateExplosion(PxActor* actor)
{
	_explode = true;

	eSFG = new ExplosionGenerator(ball->getGlobalPose().p, 20.0f, 10.0f);
	sFR->addRegistry(eSFG, ball);
}

void WorldManager::update(double t)
{
	sFR->updateForces(t);

	if (ball != nullptr) 
	{
		if (ball->getGlobalPose().p.y < -20.0f) setBallStart();
		GetCamera()->followActor(ball);
	}

	if (_nextSceneActive) 
	{
		nextScene();
		_nextSceneActive = !_nextSceneActive;
	}

	if (_activeCooldown) 
	{
		_cooldown -= t;
		if (_cooldown <= 0) 
		{
			_cooldown = _cooldownTime;
			_activeCooldown = !_activeCooldown;
			GetCamera()->changeFollow();
		}
	}

	if (_explode) eSFG->addTime(t);
}

void WorldManager::addForce(Vector3 v) 
{
	if (!GetCamera()->getFollow()) 
	{
		ball->addForce({ v.x, 0, v.z }, PxForceMode::eIMPULSE);
		GetCamera()->changeFollow();
		_cooldown = _cooldownTime;
		_activeCooldown = !_activeCooldown;
	}
}
