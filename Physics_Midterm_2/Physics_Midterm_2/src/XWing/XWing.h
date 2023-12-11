#pragma once

#include "../EntityManager/Entity.h"

class XWing : public Entity
{

public:

	Model* model;
	Model* colliderModel;

	PhysicsObject* modelPhy;
	PhysicsObject* colliderModelPhy;

	XWing();
	void CreateInstance(Model& model, Model& colliderModel);
	void AttackRun(const glm::vec3& startPos, const glm::vec3& endPos);

private:

	bool drawPath = false;

	float spacing = 2;

	float speed = 10;

	glm::vec3 startPos = glm::vec3(0);
	glm::vec3 endPos = glm::vec3(0);
	glm::vec3 direction = glm::vec3(0);

	glm::vec4 colors[3] = {
		glm::vec4(1.0, 0.0, 0.0f, 1.0f),
		glm::vec4(0.0, 1.0, 0.0f, 1.0f),
		glm::vec4(0.0, 0.0, 1.0f, 1.0f)
	};

	Renderer* renderer;

	std::vector<glm::vec3> listOfPathPoints;

	void DrawPath();

	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;
};

