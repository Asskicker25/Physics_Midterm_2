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

	std::string GetTag(PhysicsObject* phyObj);

	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;

private:

	Renderer* renderer;

	std::unordered_map<PhysicsObject*, std::string> colliderTags;

	void DrawAABBRecursive(HierarchicalAABBNode* node);
	void DrawCollisionAabb(PhysicsObject* phyObj);
};

