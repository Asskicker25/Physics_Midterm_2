#include "XWingManager.h"
#include "../Utilities/Random.h"

XWingManager::XWingManager()
{
	xwingFactory = new XWingFactory();

	InitializeEntity(this);

	InputManager::GetInstance().AddListener(this);

}

float XWingManager::GetRange(float range, float excludingRange)
{
	float value = GetRandomFloatNumber(-range, range);

	if (value > -excludingRange && value < excludingRange)
	{
		value = GetRange(range, excludingRange);

		Debugger::Print("Point Inside StarDestroyer");
		Debugger::Print("Calculating new point");
	}

	return value;
}



glm::vec3 XWingManager::GetPointInSpace()
{
	float x = GetRange(spawnRangeX, starDestroyerX);
	float y = GetRange(spawnRangeY, starDestroyerY);
	float z = GetRange(spawnRangeZ, starDestroyerZ);

	glm::vec3 newPoint = glm::vec3(x, y, z);

	Debugger::Print("Point : ", newPoint);

	return newPoint;
}


void XWingManager::Start()
{

}

XWing* XWingManager::SpawnXWing()
{
	XWing* xwing = xwingFactory->CreateXWing();


	return xwing;
}

void XWingManager::RandomAttackRun()
{
	glm::vec3 point1 = GetPointInSpace();
	glm::vec3 point2 = GetPointInSpace();

	XWing* xwing = SpawnXWing();
	xwing->AttackRun(point1, point2);

	listOfXwings.push_back(xwing);
}

void XWingManager::RandomShipAttackRun()
{
	glm::vec3 point1;
	glm::vec3 point2;


	while (true)
	{
		point1 = GetPointInSpace();
		point2 = GetPointInSpace();

		glm::vec3 diff = point2 - point1;
		glm::vec3 dir = glm::normalize(diff);
		float length = glm::length(diff);

		glm::vec3 collisionPt;
		glm::vec3 collisionNr;


		if (RayCastMesh(point1, dir, starDestroyer->starDestroyer->transform.GetTransformMatrix()
			, length, starDestroyer->starDestroyerPhyObj->GetTriangleList(), collisionPt, collisionNr))
		{
			Debugger::Print("Path found");
			break;
		}

		Debugger::Print("Calculating New Points ");
	}

	XWing* xwing = SpawnXWing();
	xwing->AttackRun(point1, point2);

	listOfXwings.push_back(xwing);

}

void XWingManager::RandomSphereRun()
{

	int random = GetRandomIntNumber(0, 1);

	Transform* sphereTransform = random == 0 ? starDestroyer->rightSphere->GetTransform() :
		starDestroyer->leftSphere->GetTransform();

	float dirX = GetRandomFloatNumber(-1.0f, 1.0f);
	float dirY = GetRandomFloatNumber(-1.0f, 1.0f);
	float dirZ = GetRandomFloatNumber(-1.0f, 1.0f);

	glm::vec3 dir = glm::vec3(dirX, dirY, dirZ);

	glm::vec3 point1 = sphereTransform->position + dir * sphereSpawnRange;
	glm::vec3 point2 = sphereTransform->position - dir * sphereSpawnRange;


	XWing* xwing = SpawnXWing();
	xwing->AttackRun(point1, point2);

	listOfXwings.push_back(xwing);
}

void XWingManager::SetStarDestroyer(StarDestroyer* starDestroyer)
{
	this->starDestroyer = starDestroyer;
}


void XWingManager::Update(float deltaTime)
{
}

void XWingManager::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	xwingFactory->AssignComponents(renderer, shader, physicsEngine);
}

void XWingManager::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}

void XWingManager::OnKeyPressed(const int& key)
{
	if (key == GLFW_KEY_2)
	{
		RandomAttackRun();
	}
	else if (key == GLFW_KEY_3)
	{
		RandomShipAttackRun();
	}
	else if (key == GLFW_KEY_4)
	{
		RandomSphereRun();
	}
}

void XWingManager::OnKeyReleased(const int& key)
{
}

void XWingManager::OnKeyHeld(const int& key)
{
}
