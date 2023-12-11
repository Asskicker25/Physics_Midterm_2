#include "PhysicsApplication.h"
#include "Utilities/RendererInstance.h"
#include "EntityManager/EntityManager.h"
#include "StarDestroyer/StarDestroyer.h"
#include "XWing/XWingManager.h"
#include "Camera/CameraHandler.h"
#include "Bullet/BulletManager.h"

void PhysicsApplication::SetUp()
{

	physicsEngine.fixedStepTime = 0.01f;
	physicsEngine.gravity.y = 0;
	moveSpeed = 25;

	RendererInstance::GetInstance().SetRenderer(&renderer);

	camera->InitializeCamera(PERSPECTIVE, windowWidth, windowHeight, 0.1f, 1000.0f, 65.0f);

	camera->transform.SetPosition(glm::vec3(-50, 20, -60));
	camera->transform.SetRotation(glm::vec3(-15, -130, 0));

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

#pragma region Shader

	explosionShader = new Shader("Assets/Shader/StarDestroyer.shader");
	explosionShader->blendMode = OPAQUE;
	explosionShader->applyInverseModel = true;
	Debugger::Print("ExplosionShaderID : ", explosionShader->GetShaderId());

#pragma endregion

	

#pragma region Light

	Model* lightModel = new Model("res/Models/DefaultSphere.fbx", false);
	lightModel->transform.SetScale(glm::vec3(0.01f));
	renderer.AddModel(lightModel, &solidColorShader);

	Light* dirLight = new Light();
	dirLight->InitializeLight(lightModel, Directional);
	dirLight->intensity = 1.2f;
	dirLight->transform->SetRotation(glm::vec3(-30, 0, 0));

	lightManager.AddLight(dirLight);
	lightManager.AddShader(explosionShader);

#pragma endregion

	CameraHandler::GetInstance().SetCamera(camera);

	BulletManager::GetInstance().Initialize();
	
	StarDestroyer* starDestroyer = new StarDestroyer();
	starDestroyer->SetShader(explosionShader);

	XWingManager* xwingManager = new XWingManager();
	xwingManager->SetStarDestroyer(starDestroyer);


	starDestroyer->SetApplication(this);

	EntityManager::GetInstance().Start();

}

void PhysicsApplication::PreRender()
{
	explosionShader->Bind();
	explosionShader->SetUniformMat("projection", camera->GetMatrix());
	explosionShader->SetUniformMat("view", view);
	explosionShader->SetUniform3f("viewPos", camera->transform.position.x, camera->transform.position.y, 
		camera->transform.position.z);


	EntityManager::GetInstance().Update(Timer::GetInstance().deltaTime);
	physicsEngine.Update(Timer::GetInstance().deltaTime);
}

void PhysicsApplication::PostRender()
{
}

void PhysicsApplication::ProcessInput(GLFWwindow* window)
{
	/*std::stringstream ssTitle;
	ssTitle << "Camera Pos : "
		<< camera->transform.position.x << " , "
		<< camera->transform.position.y << " , "
		<< camera->transform.position.z
		<< "  Camera Pitch : "
		<< camera->transform.rotation.x
		<< "  Camera Yaw : "
		<< camera->transform.rotation.y
		<< "  Camera Z : "
		<<camera->transform.rotation.z;

	std::string theTitle = ssTitle.str();*/


	glfwSetWindowTitle(window, titleMessage.c_str());
}

void PhysicsApplication::KeyCallBack(GLFWwindow* window, int& key, int& scancode, int& action, int& mods)
{
	if (action == GLFW_PRESS)
	{
		InputManager::GetInstance().OnKeyPressed(key);
	}
	else if (action == GLFW_RELEASE)
	{
		InputManager::GetInstance().OnKeyReleased(key);
	}
	else if (action == GLFW_REPEAT)
	{
		InputManager::GetInstance().OnKeyHeld(key);
	}
}

void PhysicsApplication::MouseButtonCallback(GLFWwindow* window, int& button, int& action, int& mods)
{
}
