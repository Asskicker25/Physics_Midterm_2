#include "XWingFactory.h"
#include "../EntityManager/EntityManager.h"

XWingFactory::XWingFactory()
{
    xWingModel = new Model("Assets/Models/X-Wing_Attack_xyz_n_uv.ply");
    xWingModel->transform.SetScale(glm::vec3(1.0f));

    xWingColliderModel = new Model("res/Models/DefaultSphere.fbx");
    xWingColliderModel->isWireframe = false;
    xWingColliderModel->transform.SetScale(glm::vec3(10));

}

XWing* XWingFactory::CreateXWing()
{

    XWing* xwing = new XWing();

    xwing->CreateInstance(*xWingModel, *xWingColliderModel);

    renderer->AddModel(xwing->model, shader);
    renderer->AddModel(xwing->colliderModel, shader);

    xwing->colliderModel->SetModelParent(xwing->model);

    physicsEngine->AddPhysicsObject(xwing->colliderModelPhy);
    physicsEngine->AddPhysicsObject(xwing->modelPhy);

    EntityManager::GetInstance().AddEntity("Xwing" + std::to_string(spawnedCount), xwing);

    //spawnedCount++;

    return xwing;
}

void XWingFactory::AssignComponents(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
    this->renderer = renderer;
    this->shader = shader;
    this->physicsEngine = physicsEngine;
}
