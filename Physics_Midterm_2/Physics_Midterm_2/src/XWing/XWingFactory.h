#pragma once

#include "XWing.h"

class XWingFactory
{

public:

	XWingFactory();
	XWing* CreateXWing();
	void AssignComponents(Renderer* renderer,Shader* shader, PhysicsEngine* physicsEngine);

private:

	int spawnedCount = 0;

	Renderer* renderer = nullptr;
	Shader* shader = nullptr;
	PhysicsEngine* physicsEngine = nullptr;

	Model* xWingModel = nullptr;
};

