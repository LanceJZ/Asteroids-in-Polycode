#pragma once
#include <vector>
#include "Rock.h"
#include "Explosion.h"

struct RockCount
{
	float numberActive;
	bool playerAllClear;
};

class Rocks
{
public:
	Rocks(void);

	void Setup(std::shared_ptr<CollisionScene> scene, std::shared_ptr<Player> player, std::shared_ptr<UFOControl> ufo);
	void Update(Number *elapsed);
	void NewGame(void);

private:
	int m_NumberOfRocks;
	int m_Wave;
	std::shared_ptr<Player> pPlayer;
	std::shared_ptr<UFOControl> pUFO;

	std::vector<std::unique_ptr<Explosion>> pExplosions;
	std::vector<std::unique_ptr<Rock>> pLargeRocks;
	std::vector<std::unique_ptr<Rock>> pMedRocks;
	std::vector<std::unique_ptr<Rock>> pSmallRocks;

	std::shared_ptr<CollisionScene> m_Scene;

	RockCount UpdateSmallRocks(Number *elapsed, int numberActive, bool clear);
	RockCount UpdateMedRocks(Number *elapsed, int numberActive, bool clear);
	RockCount UpdateLargeRocks(Number *elapsed, int numberActive, bool clear);
	void CreateRocks(void);
	void ClearAllRocks(void);
	void SpawnExplosion(Vector3 position, float size);
	void SpawnNewWave(int NumberOfRocks);
	void SpawnMedRocks(Vector3 position);
	void SpawnSmallRocks(Vector3 position);
};
