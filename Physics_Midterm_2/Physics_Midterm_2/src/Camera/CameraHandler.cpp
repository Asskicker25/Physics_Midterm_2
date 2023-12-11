#include "CameraHandler.h"
#include "../Utilities/Lerp.h"
#include "../Utilities/Remap.h"

#include <Graphics/Timer.h>

CameraHandler::CameraHandler()
{
	InitializeEntity(this);

	followOffset = glm::vec3(0, 1, 0);
}

CameraHandler& CameraHandler::GetInstance()
{
	static CameraHandler instance;
	return instance;
}

void CameraHandler::SetCamera(Camera* camera)
{
	this->camera = camera;
}

void CameraHandler::EnableFreeCamera()
{
	followAndLookAt = false;
}

void CameraHandler::FollowObject(Model* model)
{
	this->model = model;
	followAndLookAt = true;

	glm::vec3 pos = model->transform.position + followOffset;

	camera->transform.SetPosition(pos - model->transform.GetForward() * followDistance);
}


void CameraHandler::Start()
{
	sqDeacceleration = deaccelerationRange * deaccelerationRange;
	sqAcceleration = accelerationRange * accelerationRange;
}

void CameraHandler::Update(float deltaTime)
{
	this->deltaTime = deltaTime;

	HandleFollow();
	HandleLookAt();
}


void CameraHandler::HandleFollow()
{
	if (!followAndLookAt) return;
	if (model == nullptr) return;

	startPos = camera->transform.position;
	targetPos = model->transform.position + followOffset;

	diff = targetPos - startPos;
	dir = glm::normalize(diff);

	targetPos -= dir * followDistance;

	diff = targetPos - startPos;
	sqDist = glm::dot(diff, diff);

	float remapedValue;
	if (sqDeacceleration != 0 && sqDist <= sqDeacceleration)
	{
		remapedValue = remap(sqDist, 0, sqDeacceleration, 0, 1);
	}
	else if (sqAcceleration != 0 && sqDist >= sqAcceleration)
	{
		remapedValue = 1;
	}
	else if (sqDeacceleration != 0 && sqAcceleration != 0)
	{
		remapedValue = remap(sqDist, sqDeacceleration, sqAcceleration, 0.5, 1.0f);
	}
	else
	{
		remapedValue = 1;
	}

	timeStep = CalculateTForSpeed(timeStep, deltaTime, maxSpeed * remapedValue);


	camera->transform.SetPosition(
		Lerp(startPos, targetPos, timeStep)
	);
	
}

void CameraHandler::HandleLookAt()
{
	if (!followAndLookAt) return;
	if (model == nullptr) return;

	right = glm::cross(glm::vec3(0, 1, 0), dir);
	up = glm::cross(dir, right);
	right = glm::cross(up, dir);

	camera->transform.SetOrientationFromDirections(up, right);

	/*float pitch = camera->transform.rotation.x;
	pitch = glm::clamp(pitch, -89.0f, 89.0f);

	camera->transform.SetRotation(glm::vec3(pitch,
		camera->transform.rotation.y, 0));*/

}


void CameraHandler::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
}

void CameraHandler::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}
