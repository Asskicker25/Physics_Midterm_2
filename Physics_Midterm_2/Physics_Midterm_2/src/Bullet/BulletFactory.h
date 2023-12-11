#pragma once

#include "Bullet.h"

class BulletFactory
{
public:

	BulletFactory();
	Bullet* CreateBullet();
	void AssignComponents(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine);

private:

	int spawnedCount = 0;

	Renderer* renderer = nullptr;
	Shader* shader = nullptr;
	PhysicsEngine* physicsEngine = nullptr;

	Model* bullet = nullptr;

};

