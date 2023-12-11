#pragma once

#include "../EntityManager/Entity.h"

class XWing : public Entity
{

public:

	Model* model;

	PhysicsObject* modelPhy;

	XWing();
	void CreateInstance(Model& model);
	void AttackRun(const glm::vec3& startPos, const glm::vec3& endPos);

	void SetRayHitPoint(const glm::vec3& point);
	void HandleShooting();
	void Shoot();

private:

	bool drawPath = false;
	bool shoudlShoot = false;

	float spacing = 2;
	float turnAwayDistance = 40;

	float speed = 30;
	float sqDist = 0;
	float sqCheckDist = 0;

	glm::vec3 startPos = glm::vec3(0);
	glm::vec3 endPos = glm::vec3(0);
	glm::vec3 direction = glm::vec3(0);
	glm::vec3 rayHitPoint = glm::vec3(0);
	glm::vec3 diff = glm::vec3(0);
	

	glm::vec4 colors[5] = {
		glm::vec4(1.0, 0.0, 0.0f, 1.0f),
		glm::vec4(0.0, 1.0, 0.0f, 1.0f),
		glm::vec4(0.0, 0.0, 1.0f, 1.0f),
		glm::vec4(0.0, 0.0, 0.0f, 1.0f),
		glm::vec4(1.0, 1.0, 1.0f, 1.0f),
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

