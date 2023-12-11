#include "StarDestroyer.h"

StarDestroyer::StarDestroyer()
{
	starDestroyer = new Model();
	leftSphere = new Model();
	rightSphere = new Model();

	starDestroyerPhyObj = new PhysicsObject();
	leftSpherePhy = new PhysicsObject();
	rightSpherePhy = new PhysicsObject();

	InitializeEntity(this);

	starDestroyer->modelId = "StarDestroyer";
	leftSphere->modelId = "LeftSphere";
	rightSphere->modelId = "RightSphere";


	colliderTags[leftSpherePhy] = "LeftSphere";
	colliderTags[rightSpherePhy] = "RightSphere";
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

void StarDestroyer::Start()
{
}

void StarDestroyer::Update(float deltaTime)
{
	DrawCollisionAabb(starDestroyerPhyObj);
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

	leftSphere->LoadModel("res/Models/DefaultSphere.fbx");
	leftSphere->isWireframe = true;
	leftSphere->transform.SetPosition(glm::vec3(10, 24, 55));
	leftSphere->transform.SetScale(glm::vec3(2.5));
	leftSphere->meshes[0]->material->AsMaterial()->SetBaseColor(glm::vec4(1.0f, 0, 0, 1.0f));

	rightSphere->LoadModel("res/Models/DefaultSphere.fbx");
	rightSphere->isWireframe = true;
	rightSphere->transform.SetPosition(glm::vec3(-10, 24, 55));
	rightSphere->transform.SetScale(glm::vec3(2.5));
	rightSphere->meshes[0]->material->AsMaterial()->SetBaseColor(glm::vec4(0.0f, 1.0f, 0, 1.0f));

	renderer->AddModel(starDestroyer, shader);
	renderer->AddModel(leftSphere, shader);
	renderer->AddModel(rightSphere, shader);
	
	starDestroyerPhyObj->Initialize(starDestroyer, MESH_OF_TRIANGLES, STATIC, TRIGGER, true);
	starDestroyerPhyObj->userData = this;

	leftSpherePhy->Initialize(leftSphere, SPHERE, STATIC, TRIGGER, true);
	leftSpherePhy->userData = this;

	rightSpherePhy->Initialize(rightSphere, SPHERE, STATIC, TRIGGER, true);
	rightSpherePhy->userData = this;

	physicsEngine->AddPhysicsObject(leftSpherePhy);
	physicsEngine->AddPhysicsObject(rightSpherePhy);
	physicsEngine->AddPhysicsObject(starDestroyerPhyObj);

}

void StarDestroyer::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
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
