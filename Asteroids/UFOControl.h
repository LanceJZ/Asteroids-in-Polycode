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
	void Pause(bool paused);
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
	bool PlayerNotClear(void);

private:
	std::shared_ptr<CollisionScene> p_Scene;
	std::shared_ptr<Player> p_Player;
	std::unique_ptr<UFO> p_UFO;
	std::vector<std::unique_ptr<Explosion>> p_Explosions;

	int wave;
	int spawnCounter;
	float timer;
	float timerAmount;

	void SpawnUFO();
	void SpawnExplosion(Vector3 position, float size);
	void ResetTimer();
};