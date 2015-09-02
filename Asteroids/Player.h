#pragma once
#include "Random.h"
#include "Location.h"
#include "Shot.h"
#include "HUD.h"
//#include "Score.h"

class Player : public Location
{
public:
	Player();

	void Setup(CollisionScene *scene);
	void Update(Number *elapsed);
	void UpdateShots(Number *elapsed);
	void Turn(bool left, bool right);
	void Thrust(bool on);
	void FireShot(void);
	void Hyperspace(void);
	void Hit(void);
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
	SceneMesh *ShipBody();
	SceneMesh *ShotMesh(int shot);
	
private:
	bool turnLeft;
	bool turnRight;
	bool thrust;
	bool hit;
	bool gameOver;
	bool clearToSpawn;
	float timerExplode;
	float timerExplodeAmount;
	float timerClear;
	float timerClearAmount;

	Timer *m_ExplodeTimer;
	Timer *m_ClearTimer;
	CollisionScene *m_Scene;
	SceneMesh *m_ShipBody;
	std::vector<Entity*> m_ShipLives;

	std::unique_ptr<Shot> pShots[4];
	std::unique_ptr<HUD> pHUD;

	bool CheckClear();
	void ThrustOn();
	void Explode();
	void ResetExplodeTimer();
	void ResetClearTimer();
};
