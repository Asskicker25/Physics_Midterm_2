#pragma once

#include "../EntityManager/EntityManager.h"

class PhysicsApplication;

class StarDestroyer : public Entity
{
public:

	Model* starDestroyer;

	Sphere leftSphereShape;
	Sphere rightSphereShape;

	PhysicsObject* starDestroyerPhyObj;

	StarDestroyer();

	std::string GetTag(PhysicsObject* phyObj);

	int GetSphereDeflector(const glm::vec3& point);

	void SetApplication(PhysicsApplication* application);

	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;

private:

	Renderer* renderer;
	PhysicsApplication* application;

	int leftHealth = 100;
	int rightHealth = 100;

	std::unordered_map<PhysicsObject*, std::string> colliderTags;

	void ReducHealth(int index);

	void DrawAABBRecursive(HierarchicalAABBNode* node);
	void DrawCollisionAabb(PhysicsObject* phyObj);
};

