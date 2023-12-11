#include "PhysicsApplication.h"
#include "Utilities/RendererInstance.h"
#include "EntityManager/EntityManager.h"
#include "StarDestroyer/StarDestroyer.h"
#include "XWing/XWingManager.h"

void PhysicsApplication::SetUp()
{

	physicsEngine.fixedStepTime = 0.01f;
	physicsEngine.gravity.y = 0;
	moveSpeed = 50;


	RendererInstance::GetInstance().SetRenderer(&renderer);


	camera->InitializeCamera(PERSPECTIVE, windowWidth, windowHeight, 0.1f, 1000.0f, 65.0f);

	camera->transform.SetPosition(glm::vec3(0, 0, 0));
	camera->transform.SetRotation(glm::vec3(-20, -90, 0));

	EntityManager::GetInstance().AddToRendererAndPhysics(&renderer, &defShader, &physicsEngine);

#pragma region Skybox

	skyBox->meshes[0]->material = new SkyBoxMaterial();
	SkyBoxMaterial* skyboxMat = skyBox->meshes[0]->material->AsSkyBoxMaterial();

	skyboxMat->skyBoxTexture->LoadTexture({
		"Assets/Textures/Skybox/Right.jpg",
		"Assets/Textures/Skybox/Left.jpg",
		"Assets/Textures/Skybox/Up.jpg",
		"Assets/Textures/Skybox/Down.jpg",
		"Assets/Textures/Skybox/Front.jpg",
		"Assets/Textures/Skybox/Back.jpg",
		});

#pragma endregion


	

#pragma region Light

	Model* lightModel = new Model("res/Models/DefaultSphere.fbx", false);
	lightModel->transform.SetScale(glm::vec3(0.01f));
	renderer.AddModel(lightModel, &solidColorShader);

	Light* dirLight = new Light();
	dirLight->InitializeLight(lightModel, Directional);
	dirLight->intensity = 1.2f;
	lightManager.AddLight(dirLight);

#pragma endregion

	StarDestroyer* starDestroyer = new StarDestroyer();
	XWingManager* xwingManager = new XWingManager();

	XWing* xwing =  xwingManager->SpawnXWing();
	xwing->model->transform.SetPosition(glm::vec3(0, 20, 0));

	EntityManager::GetInstance().Start();

}

void PhysicsApplication::PreRender()
{
	physicsEngine.Update(Timer::GetInstance().deltaTime);
	EntityManager::GetInstance().Update(Timer::GetInstance().deltaTime);
}

void PhysicsApplication::PostRender()
{
}

void PhysicsApplication::ProcessInput(GLFWwindow* window)
{
}

void PhysicsApplication::KeyCallBack(GLFWwindow* window, int& key, int& scancode, int& action, int& mods)
{
}

void PhysicsApplication::MouseButtonCallback(GLFWwindow* window, int& button, int& action, int& mods)
{
}
