#include "BulletFactory.h"
#include "../EntityManager/\EntityManager.h"

BulletFactory::BulletFactory()
{
	bullet = new Model("Assets/Models/TearDropBullet.ply");
	bullet->transform.SetScale(glm::vec3( 1.0f));
}

Bullet* BulletFactory::CreateBullet()
{
	Bullet* newBullet = new Bullet();
	newBullet->CreateInstance(*bullet);

	renderer->AddModel(newBullet->model, shader);
	physicsEngine->AddPhysicsObject(newBullet->phyObj);

	EntityManager::GetInstance().AddEntity("Bullet" + std::to_string(spawnedCount), newBullet);

	return newBullet;
}

void BulletFactory::AssignComponents(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	this->renderer = renderer;
	this->shader = shader;
	this->physicsEngine = physicsEngine;
}

