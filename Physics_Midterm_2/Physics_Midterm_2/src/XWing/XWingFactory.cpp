#include "XWingFactory.h"
#include "../EntityManager/EntityManager.h"

XWingFactory::XWingFactory()
{
    xWingModel = new Model("Assets/Models/X-Wing_Attack_xyz_n_uv.ply");
    xWingModel->transform.SetScale(glm::vec3(0.1f));

    xWingColliderModel = new Model("res/Models/DefaultSphere.fbx");
    xWingColliderModel->isWireframe = true;
    xWingColliderModel->transform.SetScale(glm::vec3(10));

}

XWing* XWingFactory::CreateXWing()
{

    XWing* xwing = new XWing();

    xwing->CreateInstance(*xWingModel, *xWingColliderModel);

    renderer->AddModel(xwing->model, shader);
    renderer->AddModel(xwing->colliderModel, shader);

    xwing->colliderModel->SetModelParent(xwing->model);

    physicsEngine->AddPhysicsObject(xwing->phyObj);

    EntityManager::GetInstance().AddEntity("Xwing" + std::to_string(spawnedCount), xwing);

    return xwing;
}

void XWingFactory::AssignComponents(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
    this->renderer = renderer;
    this->shader = shader;
    this->physicsEngine = physicsEngine;
}
