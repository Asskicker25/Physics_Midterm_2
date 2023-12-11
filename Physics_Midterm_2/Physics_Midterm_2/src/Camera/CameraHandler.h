#pragma once

#include "../EntityManager/Entity.h"
#include <Graphics/Camera.h>
#include <Graphics/Model.h>

class CameraHandler : public Entity
{

public:

	CameraHandler();

	static CameraHandler& GetInstance();
	void SetCamera(Camera* camera);

	void EnableFreeCamera();

	void FollowObject(Model* model);

private:

	Camera* camera;
	Model* model;

	bool followAndLookAt = false;

	float followDistance = 100;
	float speed = 0;
	float maxSpeed = 10;
	float accelerationRange = 0;
	float deaccelerationRange = 0;

	float sqDist = 0;
	float sqAcceleration = 60;
	float sqDeacceleration = 20;

	float timeStep = 0;
	float deltaTime = 0;

	glm::vec3 dir;
	glm::vec3 diff;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 startPos;
	glm::vec3 targetPos;
	glm::vec3 followOffset;


	void HandleFollow();
	void HandleLookAt();

	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;
};

