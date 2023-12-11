#pragma once

#include "../EntityManager/EntityManager.h"

#include "BulletFactory.h"

class BulletManager : public Entity
{

public:

	BulletManager();
	static BulletManager& GetInstance();

	void Initialize();
	Bullet* SpawnBullet();

private:
	BulletFactory* bulletFactory;

	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;

};

