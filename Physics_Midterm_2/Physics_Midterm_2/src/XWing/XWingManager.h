#pragma once

#include "../EntityManager/EntityManager.h"
#include "../InputManager/InputManager.h"
#include "XWingFactory.h"
#include "../StarDestroyer/StarDestroyer.h"

class XWingManager : public Entity, public iInputListener
{
public:

	XWingFactory* xwingFactory;

	XWingManager();

	XWing* SpawnXWing();

	void RandomAttackRun();
	void RandomShipAttackRun();
	void RandomSphereRun();

	void SetStarDestroyer(StarDestroyer* starDestroyer);

private:

	float starDestroyerX = 65;
	float starDestroyerY = 40;
	float starDestroyerZ = 90;

	float spawnRangeX = 95;
	float spawnRangeY = 70;
	float spawnRangeZ = 120;

	float sphereSpawnRange = 150;

	glm::vec3 GetPointInSpace();
	float GetRange(float range, float excludingRange);

	std::vector<XWing*> listOfXwings;

	StarDestroyer* starDestroyer;


	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;

	// Inherited via iInputListener
	void OnKeyPressed(const int& key) override;
	void OnKeyReleased(const int& key) override;
	void OnKeyHeld(const int& key) override;
};

