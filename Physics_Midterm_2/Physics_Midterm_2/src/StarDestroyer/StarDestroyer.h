#pragma once

#include "../EntityManager/EntityManager.h"

class StarDestroyer : public Entity
{
public:
	Model* model;
	PhysicsObject* phyObj;

	StarDestroyer();

	void DrawAABBRecursive(HierarchicalAABBNode* node);

	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;

private:

	Renderer* renderer;

};

