#include "XWing.h"
#include "../StarDestroyer/StarDestroyer.h"
#include "../Bullet/BulletManager.h"
#include "../Camera/CameraHandler.h"

XWing::XWing()
{
	model = new Model();

	modelPhy = new PhysicsObject();

	sqCheckDist = turnAwayDistance * turnAwayDistance;
}

void XWing::CreateInstance(Model& model)
{
	this->model->CopyFromModel(model);


	modelPhy->properties.colliderScale = 10;
	modelPhy->Initialize(this->model, SPHERE, DYNAMIC, TRIGGER,true);
	modelPhy->userData = this;

	modelPhy->AssignCollisionCallback([this](PhysicsObject* other)
		{
			Entity* entity = (Entity*)other->userData;

			if (entity->tag == "StarDestroyer")
			{
				StarDestroyer* starDestroyer = (StarDestroyer*)entity;

				std::string tag = starDestroyer->GetTag(other);

				if (tag == "LeftSphere")
				{
					Debugger::Print("LeftSphere");
					modelPhy->isCollisionInvoke = false;
					Shoot();
				}
				else if (tag == "RightSphere")
				{
					Debugger::Print("RightSphere");
					modelPhy->isCollisionInvoke = false;
					Shoot();
				}
				else if (tag == "Ship")
				{
					modelPhy->isCollisionInvoke = false;
					Shoot();
				}
			}
		});
}

void XWing::AttackRun(const glm::vec3& startPos, const glm::vec3& endPos)
{
	this->startPos = startPos;
	this->endPos = endPos;

	direction = endPos - startPos;

	float length = glm::length(direction);

	float count = length / spacing;

	direction = glm::normalize(direction);

	glm::vec3 pos;

	for (int i = 0; i < count; i++)
	{
		pos = startPos + (direction * (float)i * spacing );
		listOfPathPoints.push_back(pos);
	}

	model->transform.SetPosition(startPos);

	glm::vec3 right = glm::cross(glm::vec3(0, 1, 0), direction);
	glm::vec3 up = glm::cross(direction, right);

	model->transform.SetOrientationFromDirections(up, right);

	modelPhy->velocity = direction * speed;


	drawPath = true;
}

void XWing::SetRayHitPoint(const glm::vec3& point)
{
	this->rayHitPoint = point;
}

void XWing::HandleShooting()
{
	if (!shoudlShoot) return;

	Bullet* bullet = BulletManager::GetInstance().SpawnBullet();
	bullet->model->transform.SetPosition(model->transform.position);

	glm::vec3 right = glm::cross(glm::vec3(0, 1, 0), direction);
	glm::vec3 up = glm::cross(direction, right);

	bullet->model->transform.SetOrientationFromDirections(up, -right);

	bullet->SetVelocity(direction);

	modelPhy->velocity = -modelPhy->velocity;

	model->transform.SetOrientationFromDirections(up, -right);

	CameraHandler::GetInstance().EnableFreeCamera(model->modelId);

	shoudlShoot = false;

}

void XWing::Shoot()
{
	glm::vec3 shootDir = glm::normalize(modelPhy->velocity);

	shoudlShoot = true;
}

void XWing::DrawPath()
{
	if (!drawPath) return;

	for (glm::vec3 pos : listOfPathPoints)
	{
		renderer->DrawSphere(pos, 0.01, colors[1]);
	}

	renderer->DrawSphere(startPos, 2, colors[0]);
	renderer->DrawSphere(endPos, 2, colors[2]);

	Sphere* sphere = dynamic_cast<Sphere*>(modelPhy->GetTransformedPhysicsShape());

	//renderer->DrawSphere(sphere->position, sphere->radius, colors[4]);
	//renderer->DrawSphere(rayHitPoint, 5, colors[3]);

}

void XWing::Start()
{
}

void XWing::Update(float deltaTime)
{
	HandleShooting();
	DrawPath();
}

void XWing::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	this->renderer = renderer;
}

void XWing::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}
