#pragma once

#include "../EntityManager/Entity.h"

class Bullet : public Entity
{
public:

	Bullet();

	float speed = 10;

	Model* model;
	PhysicsObject* phyObj;

	void CreateInstance(Model& model);
	void SetVelocity(const glm::vec3& dir);

	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;
};

