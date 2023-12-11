#include "BulletManager.h"

BulletManager::BulletManager()
{
	bulletFactory = new BulletFactory();
	InitializeEntity(this);
}

BulletManager& BulletManager::GetInstance()
{
	static BulletManager instance;
	return instance;
}

void BulletManager::Initialize()
{
	std::cout << "Initialized" << std::endl;
}

Bullet* BulletManager::SpawnBullet()
{
	Bullet* bullet = bulletFactory->CreateBullet();
	return bullet;
}

void BulletManager::Start()
{
}

void BulletManager::Update(float deltaTime)
{
}

void BulletManager::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	bulletFactory->AssignComponents(renderer, shader, physicsEngine);
}

void BulletManager::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}
