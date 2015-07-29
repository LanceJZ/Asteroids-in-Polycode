#pragma once
#include "Random.h"
#include "Location.h"
#include "Shot.h"

class Player : public Location
{
public:
	Player();

	void Setup(CollisionScene *scene);
	void Update(Number *elapsed);
	void UpdateShots(Number *elapsed);
	void Turn(bool left, bool right);
	void Thrust(bool on);
	void FireShot();
	void Hyperspace();
	void Hit();
	void SetLives(int numberOfLives);
	void Activate(void);
	void Deactivate(void);
	void NewGame(void);
	void Reset(void);
	void DeactivateShot(int shot);
	bool ShotActive(int shot);
	Vector3 Position();
	float ShotRadius(int shot);
	SceneMesh *ShipBody();
	SceneMesh *ShotMesh(int shot);

private:
	bool turnLeft;
	bool turnRight;
	bool thrust;
	bool hit;
	int lives;
	float timerExplode;
	float timerExplodeAmount;
	float timerClear;
	float timerClearAmount;

	Timer *m_ExplodeTimer;
	Timer *m_ClearTimer;
	CollisionScene *m_Scene;
	SceneMesh *m_ShipBody;
	std::unique_ptr<Shot> pShots[4];

	void ThrustOn();
	void Explode();
	void ResetExplodeTimer();
	void ResetClearTimer();
};
