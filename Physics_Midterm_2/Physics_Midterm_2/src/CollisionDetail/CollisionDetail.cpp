#include "CollisionDetail.h"

CollisionDetail::CollisionDetail()
{
	InitializeEntity(this);

	model = new Model("res/Models/DefaultSphere.fbx");
	model->transform.SetScale(glm::vec3(0.3f));
	model->meshes[0]->material->AsMaterial()->SetBaseColor(glm::vec4(0.8, 0.5, 0.9, 1.0f));
}

CollisionDetail& CollisionDetail::GetInstance()
{
	static CollisionDetail instance;
	return instance;
}

void CollisionDetail::AddPoint(const glm::vec3& collisionPoint)
{
	if (destroyed) return;

	Model* newModel = new Model();
	newModel->CopyFromModel(*model);
	newModel->transform.SetPosition(collisionPoint);
	renderer->AddModel(newModel, shader);

	listOfCollisionModels.push_back(newModel);
	//listOfCollisionPoints.push_back(collisionPoint);

}

void CollisionDetail::Destroy()
{
	destroyed = true;
	for (Model* model : listOfCollisionModels)
	{
		renderer->RemoveModel(model);
	}
}

void CollisionDetail::Start()
{
}

void CollisionDetail::Update(float deltaTime)
{

	/*for (glm::vec3& point : listOfCollisionPoints)
	{
		renderer->DrawSphere(point, 1, );
	}*/
}

void CollisionDetail::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	this->renderer = renderer;
	this->shader = shader;
}

void CollisionDetail::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}
