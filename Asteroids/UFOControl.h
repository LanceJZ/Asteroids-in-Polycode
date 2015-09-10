#pragma once
#include "UFO.h"
#include "Explosion.h"

class UFOControl : public Polycode::Timer
{
public:
	UFOControl();
	void Setup(std::shared_ptr<CollisionScene> scene, std::shared_ptr<Player> player);
	void Update(Number *elapsed);
	void WaveNumber(int Wave);
	void HitRock(void);
	void Deactivate(void);
	void DeactivateShot(void);
	void NewGame(void);
	float ShotRadius(void);
	float Radius(void);
	SceneMesh *ShotMesh(void);
	SceneMesh *ShipBody(void);
	Vector3 Position(void);
	bool ShotActive(void);
	bool Active(void);

private:
	std::shared_ptr<CollisionScene> m_Scene;
	std::shared_ptr<Player> pPlayer;
	std::unique_ptr<UFO> pUFO;
	std::vector<std::unique_ptr<Explosion>> pExplosions;

	int wave;
	int spawnCounter;
	float timer;
	float timerAmount;

	void SpawnUFO();
	void SpawnExplosion(Vector3 position, float size);
	void ResetTimer();
};