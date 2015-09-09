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

	std::unique_ptr<HUD> p_HUD;
	SceneMesh *m_ShipMesh;

private:
	bool m_ShipTurning;
	bool m_Hit;
	bool m_GameOver;
	bool m_ClearToSpawn;
	bool m_ThrustOn;
	int m_GameOverDisplay;
	float m_TimerExplodeAmount;
	float m_TimerClearAmount;
	float m_TimerGameOverAmount;

	std::unique_ptr<Timer> p_ExplodeTimer;
	std::unique_ptr<Timer> p_ClearTimer;
	std::unique_ptr<Timer> p_GameOverTimer;

	std::shared_ptr<CollisionScene> p_Scene;
	std::vector<Entity*> p_ShipLives;

	std::unique_ptr<Shot> p_Shots[4];

	void ApplyThrust(void);
	void Explode(void);
	void ResetExplodeTimer(void);
	void ResetClearTimer(void);
	void ResetGameOverTimer(void);
	bool CheckClear(void);
};
