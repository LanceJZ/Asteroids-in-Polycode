#pragma once
#include "UFO.h"

class UFOControl : public Polycode::Timer
{
public:
	UFOControl();
	void Setup(CollisionScene *scene, std::shared_ptr<Player> player);
	void Update(Number *elapsed);
	void WaveNumber(int Wave);
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