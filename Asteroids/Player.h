#pragma once
#include "Random.h"
#include "Location.h"
#include "Shot.h"
#include "HUD.h"
//#include "Score.h"

class Player : public Location
{
public:
	Player(void);

	void Setup(CollisionScene *scene);
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
	bool GotHit(void);
	void SetClear(void);
	void Activate(void);
	void Deactivate(void);
	void NewGame(void);
	void Reset(void);
	void DeactivateShot(int shot);
	bool ShotActive(int shot);
	Vector3 Position(void);
	float ShotRadius(int shot);
	SceneMesh *ShipBody(void);
	SceneMesh *ShotMesh(int shot);

	std::unique_ptr<HUD> pHUD;

private:
	bool shipTurning;
	bool hit;
	bool gameOver;
	bool clearToSpawn;
	bool thrustOn;
	int gameOverDisplay;
	float timerExplode;
	float timerExplodeAmount;
	float timerClear;
	float timerClearAmount;
	float timerGameOver;
	float timerGameOverAmount;

	Timer *m_ExplodeTimer;
	Timer *m_ClearTimer;
	Timer *m_GameOverTimer;

	CollisionScene *m_Scene;
	SceneMesh *m_ShipBody;
	std::vector<Entity*> m_ShipLives;

	std::unique_ptr<Shot> pShots[4];

	void ApplyThrust(void);
	void Explode(void);
	void ResetExplodeTimer(void);
	void ResetClearTimer(void);
	void ResetGameOverTimer(void);
	bool CheckClear(void);
};
