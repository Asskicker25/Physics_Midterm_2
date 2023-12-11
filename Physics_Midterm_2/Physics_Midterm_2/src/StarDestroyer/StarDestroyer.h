#pragma once

#include "../EntityManager/EntityManager.h"

class PhysicsApplication;

class StarDestroyer : public Entity
{
public:

	bool startExplosion = false;

	Model* starDestroyer;

	Sphere leftSphereShape;
	Sphere rightSphereShape;

	PhysicsObject* starDestroyerPhyObj;

	StarDestroyer();

	std::string GetTag(PhysicsObject* phyObj);

	int GetSphereDeflector(const glm::vec3& point);

	void SetApplication(PhysicsApplication* application);

	void SetShader(Shader* shader);



	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;

private:

	Renderer* renderer;
	Shader* shader;
	PhysicsApplication* application;

	int leftHealth = 100;
	int rightHealth = 100;

	float offset = 0;

	float explosionSpeed = 700;


	std::unordered_map<PhysicsObject*, std::string> colliderTags;

	void ReducHealth(int index);
	void SetExplosionOffset();

	void DrawAABBRecursive(HierarchicalAABBNode* node);
	void DrawCollisionAabb(PhysicsObject* phyObj);
};

