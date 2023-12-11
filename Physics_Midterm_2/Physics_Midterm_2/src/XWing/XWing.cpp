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

void XWing::Start()
{
}

void XWing::Update(float deltaTime)
{
}

void XWing::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
}

void XWing::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}
