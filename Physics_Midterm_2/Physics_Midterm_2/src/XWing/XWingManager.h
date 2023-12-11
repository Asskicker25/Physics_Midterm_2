#pragma once

#include "../EntityManager/EntityManager.h"
#include "XWingFactory.h"

class XWingManager : public Entity
{
public:

	XWingFactory* xwingFactory;

	XWingManager();

	XWing* SpawnXWing();


private:

	Shader* alphaBlendShader;
	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;
};

