#include "Bullet.h"
#include "../StarDestroyer/StarDestroyer.h"
#include "../CollisionDetail/CollisionDetail.h"

Bullet::Bullet()
{
	model = new Model();
	phyObj = new PhysicsObject();
}

void Bullet::CreateInstance(Model& model)
{
	this->model->CopyFromModel(model);

	phyObj->properties.colliderScale = 0.1f;
	phyObj->properties.offset = glm::vec3(0, 0, 0.8);
	phyObj->Initialize(this->model, SPHERE, DYNAMIC, TRIGGER, true);

	phyObj->AssignCollisionCallback([this](PhysicsObject* other)
		{
			if (other->userData == nullptr) return;

			Entity* entity = (Entity*)other->userData;

			if (entity->tag == "StarDestroyer")
			{
				StarDestroyer* starDestroyer = (StarDestroyer*)entity;

				std::string tag = starDestroyer->GetTag(other);

				if (tag == "Ship")
				{
					std::vector<glm::vec3> collisionPts = phyObj->GetCollisionPoints();
					glm::vec3 point = GetCollisionPoint(collisionPts);

					int result = starDestroyer->GetSphereDeflector(point);

					/*if (result == -1)
					{
					}*/
					CollisionDetail::GetInstance().AddPoint(point);

					Destroy();
				}
			}
		});

}

void Bullet::SetVelocity(const glm::vec3& dir)
{
	phyObj->velocity = dir * speed;
}

glm::vec3 Bullet::GetCollisionPoint(std::vector<glm::vec3>& collisionPt)
{
	glm::vec3 point = glm::vec3(0);

	for (glm::vec3 pt : collisionPt)
	{
		point += pt;
	}

	point = point / (float)collisionPt.size();

	return point;
}

void Bullet::Start()
{
}

void Bullet::Update(float deltaTime)
{

	Sphere* sphere = dynamic_cast<Sphere*> (phyObj->GetTransformedPhysicsShape());

	renderer->DrawSphere(sphere->position, sphere->radius, glm::vec4(1));
}

void Bullet::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	this->renderer = renderer;
}

void Bullet::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
	renderer->RemoveModel(model);
	physicsEngine->RemovePhysicsObject(phyObj);
}
