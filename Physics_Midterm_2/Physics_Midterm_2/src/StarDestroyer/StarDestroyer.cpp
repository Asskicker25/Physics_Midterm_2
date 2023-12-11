#include "StarDestroyer.h"
#include <Physics/PhysicsShapeAndCollision.h>
#include "../PhysicsApplication.h"

StarDestroyer::StarDestroyer()
{
	starDestroyer = new Model();

	starDestroyerPhyObj = new PhysicsObject();

	InitializeEntity(this);

	starDestroyer->modelId = "StarDestroyer";

	colliderTags[starDestroyerPhyObj] = "Ship";

}

std::string StarDestroyer::GetTag(PhysicsObject* phyObj)
{
	std::unordered_map<PhysicsObject*, std::string>::iterator it = colliderTags.find(phyObj);

	if (it != colliderTags.end())
	{
		return colliderTags[phyObj];
	}
	
	return "";
}

int StarDestroyer::GetSphereDeflector(const glm::vec3& point)
{
	if (IsPointInisideSphere(point, rightSphereShape))
	{
		Debugger::Print("RightSphere");
		ReducHealth(0);
		return 0;
	}

	if (IsPointInisideSphere(point, leftSphereShape))
	{
		Debugger::Print("LeftSphere");
		ReducHealth(1);
		return 1;
	}

	return -1;
}

void StarDestroyer::SetApplication(PhysicsApplication* application)
{
	this->application = application;
	application->titleMessage = 
		"Left Sphere : " + std::to_string(leftHealth) + "  Right Sphere : " + std::to_string(rightHealth);
}

void StarDestroyer::SetShader(Shader* shader)
{
	this->shader = shader;
	renderer->AddModel(starDestroyer, shader);
}

void StarDestroyer::Start()
{
}

void StarDestroyer::Update(float deltaTime)
{
	SetExplosionOffset();

	DrawCollisionAabb(starDestroyerPhyObj);

	/*renderer->DrawSphere(leftSphereShape.position, leftSphereShape.radius);
	renderer->DrawSphere(rightSphereShape.position, rightSphereShape.radius);*/

	//DrawAABBRecursive(phyObj->hierarchialAABB->rootNode);
}

void StarDestroyer::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	this->renderer = renderer;
	tag = "StarDestroyer";

	starDestroyer->LoadModel("Assets/Models/Stardestroyer_CompleteModel_LayersJoined (decimate 10 per, 167,274 vert, 59,360 face).ply");
	starDestroyer->transform.SetScale(glm::vec3(0.1f));
	starDestroyer->meshes[0]->material->AsMaterial()->SetBaseColor(glm::vec4(0.4, 0.4, 0.4, 1.0f));
	//starDestroyer->isWireframe = true;


	leftSphereShape.position = glm::vec3(10, 24, 55.5);
	leftSphereShape.radius = 3.0f;

	rightSphereShape.position = glm::vec3(-10, 24, 55.5);
	rightSphereShape.radius = 3.0f;


	//renderer->AddModel(starDestroyer, shader);
	
	starDestroyerPhyObj->Initialize(starDestroyer, MESH_OF_TRIANGLES, STATIC, TRIGGER, true);
	starDestroyerPhyObj->userData = this;

	physicsEngine->AddPhysicsObject(starDestroyerPhyObj);

}

void StarDestroyer::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}

void StarDestroyer::ReducHealth(int index)
{
	if (index == 0)
	{
		rightHealth -= 25;
		rightHealth = glm::clamp(rightHealth, 0, 100);
	}
	else if (index == 1)
	{
		leftHealth -= 25;
		leftHealth = glm::clamp(leftHealth, 0, 100);
	}

	if (leftHealth == 0 && rightHealth == 0)
	{
		application->titleMessage = "He's Dead Jim...!               You've Destroyerd the StarDestroyer!!!";

		startExplosion = true;

		system("cls");
		Debugger::Print("Both Sphere Deflectors Down!!!");
		Debugger::Print("Star Destroyer, Destroyed!!!");
	}
	else
	{
		application->titleMessage =
			"Left Sphere : " + std::to_string(leftHealth) + "  Right Sphere : " + std::to_string(rightHealth);
	}
	

}

void StarDestroyer::SetExplosionOffset()
{
	if (!startExplosion) return;

	shader->Bind();

	offset += Timer::GetInstance().deltaTime * explosionSpeed;

	shader->SetUniform1f("explosionOffset", offset);

}

void StarDestroyer::DrawAABBRecursive(HierarchicalAABBNode* node)
{
	if (node == nullptr) return;

	/*if (node->nodeIndex == aabbDrawDepthIndex)
	{
		renderer.DrawAABB(GetGraphicsAabb(node->GetModelAABB()), aabbColor[2]);
		return;
	}*/

	if (node->triangleIndices.size() != 0)
	{
		renderer->DrawAABB(GetGraphicsAabb(node->GetModelAABB()), glm::vec4(0,0,1,1));
	}

	if (node->leftNode == nullptr) return;

	DrawAABBRecursive(node->leftNode);
	DrawAABBRecursive(node->rightNode);

}

void StarDestroyer::DrawCollisionAabb(PhysicsObject* phyObj)
{
	std::vector<Aabb> collisionAabs = phyObj->GetCollisionAabbs();

	for (Aabb aabb : collisionAabs)
	{
		renderer->DrawAABB(GetGraphicsAabb(aabb), glm::vec4(0, 1, 0, 1));
	}
}
