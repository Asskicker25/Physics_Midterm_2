#pragma once

#include "../EntityManager/Entity.h"

class CollisionDetail : public Entity
{

public:
	CollisionDetail();

	static CollisionDetail& GetInstance();

	void AddPoint(const glm::vec3& collisionPoint);

	void Destroy();

private:

	Renderer* renderer;
	Shader* shader;

	Model* model;

	bool destroyed = false;

	std::vector<Model*> listOfCollisionModels;

	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;


};

