#pragma once
#include <vector>
#include "Rock.h"

class Rocks
{
public:
	Rocks(void);

	void Setup(CollisionScene *scene, std::shared_ptr<Player> player, std::shared_ptr<UFOControl> ufo);
	void Update(Number *elapsed);
	void NewGame(void);

private:
	int m_NumberOfRocks;
	int m_Wave;
	std::shared_ptr<Player> pPlayer;
	std::shared_ptr<UFOControl> pUFO;

	std::vector<std::unique_ptr<Rock>> pLargeRocks;
	std::vector<std::unique_ptr<Rock>> pMedRocks;
	std::vector<std::unique_ptr<Rock>> pSmallRocks;

	CollisionScene *m_Scene;

	void CreateRocks(void);
	void ClearAllRocks(void);
	void SpawnNewWave(int NumberOfRocks);
	void SpawnMedRocks(Vector3 location);
	void SpawnSmallRocks(Vector3 location);
};
