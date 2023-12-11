#pragma once

#include "../EntityManager/EntityManager.h"

class StarDestroyer : public Entity
{
public:

	Model* starDestroyer;
	Model* leftSphere;
	Model* rightSphere;

	PhysicsObject* starDestroyerPhyObj;
	PhysicsObject* leftSpherePhy;
	PhysicsObject* rightSpherePhy;

	StarDestroyer();


	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;

private:

	Renderer* renderer;

	void DrawAABBRecursive(HierarchicalAABBNode* node);
	void DrawCollisionAabb(PhysicsObject* phyObj);
};

