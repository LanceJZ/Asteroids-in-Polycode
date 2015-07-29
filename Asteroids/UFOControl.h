#pragma once
#include "UFO.h"

class UFOControl : public Polycode::Timer
{
public:
	UFOControl();
	void Setup(CollisionScene *scene, std::shared_ptr<Player> player);
	void Update(Number *elapsed);
	void WaveNumber(int Wave);
	Vector3 Position(void);
	SceneMesh *ShipBody(void);
	void Deactivate(void);
	void DeactivateShot(void);
	float ShotRadius(void);
	float Radius(void);
	bool Active(void);
	SceneMesh *ShotMesh(void);
	bool ShotActive(void);

private:
	CollisionScene *m_Scene;
	std::shared_ptr<Player> pPlayer;
	std::unique_ptr<UFO> pUFO;

	int wave;
	int spawnCounter;
	float timer;
	float timerAmount;

	void SpawnUFO();
	void ResetTimer();
};