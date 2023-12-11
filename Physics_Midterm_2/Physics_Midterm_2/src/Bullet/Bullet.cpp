#include "Bullet.h"

Bullet::Bullet()
{
	model = new Model();
	phyObj = new PhysicsObject();
}

void Bullet::CreateInstance(Model& model)
{
	this->model->CopyFromModel(model);
	phyObj->Initialize(this->model, SPHERE, DYNAMIC, TRIGGER, true);

}

void Bullet::SetVelocity(const glm::vec3& dir)
{
	phyObj->velocity = dir * speed;
}

void Bullet::Start()
{
}

void Bullet::Update(float deltaTime)
{
}

void Bullet::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
}

void Bullet::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}
