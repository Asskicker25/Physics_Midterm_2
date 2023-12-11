#include "XWingFactory.h"
#include "../EntityManager/EntityManager.h"

XWingFactory::XWingFactory()
{
    xWingModel = new Model("Assets/Models/X-Wing_Attack_xyz_n_uv.ply");
    xWingModel->transform.SetScale(glm::vec3(0.1f));

}

XWing* XWingFactory::CreateXWing()
{

    XWing* xwing = new XWing();

    std::string entityId = "Xwing" + std::to_string(spawnedCount);

    xwing->CreateInstance(*xWingModel);

    renderer->AddModel(xwing->model, shader);

    xwing->model->modelId = entityId;

    physicsEngine->AddPhysicsObject(xwing->modelPhy);

    EntityManager::GetInstance().AddEntity(entityId, xwing);

    spawnedCount++;

    return xwing;
}

void XWingFactory::AssignComponents(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
    this->renderer = renderer;
    this->shader = shader;
    this->physicsEngine = physicsEngine;
}
