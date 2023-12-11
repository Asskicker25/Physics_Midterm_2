#pragma once

#include "../EntityManager/Entity.h"

class CollisionDetail : public Entity
{

public:
	CollisionDetail();

	static CollisionDetail& GetInstance();

	void AddPoint(const glm::vec3& collisionPoint);

private:

	Renderer* renderer;
	Shader* shader;

	Model* model;

	std::vector<glm::vec3> listOfCollisionPoints;

	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;


};

