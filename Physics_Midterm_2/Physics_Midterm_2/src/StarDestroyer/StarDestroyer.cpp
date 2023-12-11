#include "StarDestroyer.h"

StarDestroyer::StarDestroyer()
{
	model = new Model();
	phyObj = new PhysicsObject();

	InitializeEntity(this);

}

void StarDestroyer::Start()
{
}

void StarDestroyer::Update(float deltaTime)
{
	DrawAABBRecursive(phyObj->hierarchialAABB->rootNode);
}

void StarDestroyer::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	this->renderer = renderer;

	model->LoadModel("Assets/Models/Stardestroyer_CompleteModel_LayersJoined (decimate 10 per, 167,274 vert, 59,360 face).ply");
	model->transform.SetScale(glm::vec3(0.1f));
	model->meshes[0]->material->AsMaterial()->SetBaseColor(glm::vec4(0.7, 0.7, 0.7, 1.0f));

	renderer->AddModel(model, shader);
	
	phyObj->Initialize(model, MESH_OF_TRIANGLES, STATIC, TRIGGER, true);
	phyObj->userData = this;

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
