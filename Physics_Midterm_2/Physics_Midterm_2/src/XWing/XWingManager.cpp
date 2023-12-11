#include "XWingManager.h"

XWingManager::XWingManager()
{
	xwingFactory = new XWingFactory();

	InitializeEntity(this);

}

void XWingManager::Start()
{
}

XWing* XWingManager::SpawnXWing()
{
	XWing* xwing = xwingFactory->CreateXWing();

	return xwing;
}


void XWingManager::Update(float deltaTime)
{
}

void XWingManager::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	xwingFactory->AssignComponents(renderer, shader, physicsEngine);
}

void XWingManager::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}
