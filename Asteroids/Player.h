#pragma once
#include "Location.h"
#include "Random.h"
#include "Shot.h"
#include "HUD.h"

class Player : public Location
{
public:
	Player(void);

	void Setup(std::shared_ptr<CollisionScene> scene);
	void Update(Number *elapsed);
	void UpdateShots(Number *elapsed);
	void UpdateGameOver(void);
	void TurnLeft(void);
	void TurnRight(void);
	void TurnOff(void);
	void ThrustOn(void);
	void ThrustOff(void);
	void FireShot(void);
	void Hyperspace(void);
	void Hit(void);
	void UpdateLivesDisplay(void);
	void GotPoints(int points);
	void SetClear(void);
	void Activate(void);
	void Deactivate(void);
	void NewGame(void);
	void Reset(void);
	void DeactivateShot(int shot);
	bool ShotActive(int shot);
	bool GotHit(void);
	float ShotRadius(int shot);
	Vector3 Position(void);
	Vector3 ShotPosition(int shot);
	SceneMesh *ShotMesh(int shot);

	std::unique_ptr<HUD> pHUD;
	SceneMesh *m_ShipMesh;

private:
	bool shipTurning;
	bool hit;
	bool gameOver;
	bool clearToSpawn;
	bool thrustOn;
	int gameOverDisplay;
	float timerExplodeAmount;
	float timerClearAmount;
	float timerGameOverAmount;

	std::unique_ptr<Timer> m_ExplodeTimer;
	std::unique_ptr<Timer> m_ClearTimer;
	std::unique_ptr<Timer> m_GameOverTimer;

	std::shared_ptr<CollisionScene> m_Scene;
	std::vector<Entity*> m_ShipLives;

	std::unique_ptr<Shot> pShots[4];

	void ApplyThrust(void);
	void Explode(void);
	void ResetExplodeTimer(void);
	void ResetClearTimer(void);
	void ResetGameOverTimer(void);
	bool CheckClear(void);
};
