#include "XWing.h"

XWing::XWing()
{
	model = new Model();
	colliderModel = new Model();
	phyObj = new PhysicsObject();
}

void XWing::CreateInstance(Model& model, Model& colliderModel)
{
	this->model->CopyFromModel(model);
	this->colliderModel->CopyFromModel(colliderModel);

	this->colliderModel->isWireframe = true;

	phyObj->Initialize(this->colliderModel, SPHERE, DYNAMIC, TRIGGER, true);
	phyObj->userData = this;
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


	drawPath = true;
}

void XWing::DrawPath()
{
	if (!drawPath) return;

	for (glm::vec3 pos : listOfPathPoints)
	{
		renderer->DrawSphere(pos, 2, colors[1]);
	}

	renderer->DrawSphere(startPos, 10, colors[0]);
	renderer->DrawSphere(endPos, 10, colors[2]);

}

void XWing::Start()
{
}

void XWing::Update(float deltaTime)
{
	DrawPath();
}

void XWing::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	this->renderer = renderer;
}

void XWing::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}
