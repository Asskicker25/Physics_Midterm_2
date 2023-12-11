#pragma once

#include "../EntityManager/Entity.h"

class XWing : public Entity
{

public:

	Model* model;
	Model* colliderModel;
	PhysicsObject* phyObj;

	XWing();
	void CreateInstance(Model& model, Model& colliderModel);

private:

	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;
};

