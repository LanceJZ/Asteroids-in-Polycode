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
	void GotPoints(int points);
	void DeactivateShot(int shot);
	void Pause(bool paused);
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
	void SetClear(void);
	void Activate(void);
	void Deactivate(void);
	void NewGame(void);
	void Reset(void);

	bool ShotActive(int shot);
	bool m_Hit;
	bool m_Spawn;
	bool m_GameOver;
	float ShotRadius(int shot);
	Vector3 Position(void);
	Vector3 ShotPosition(int shot);
	SceneMesh *ShotMesh(int shot);

	std::unique_ptr<HUD> p_HUD;
	SceneMesh *m_ShipMesh;

private:
	bool m_ShipTurning;
	bool m_ClearToSpawn;
	bool m_ThrustOn;
	bool m_ThrustFlameOn;
	int m_GameOverDisplay;
	float m_ExplodeTimerAmount;
	float m_ClearTimerAmount;
	float m_GameOverTimerAmount;
	float m_FlameTimerAmount;

	std::unique_ptr<Timer> p_ExplodeTimer;
	std::unique_ptr<Timer> p_ClearTimer;
	std::unique_ptr<Timer> p_GameOverTimer;
	std::unique_ptr<Timer> p_FlameTimer;

	std::shared_ptr<CollisionScene> p_Scene;
	std::unique_ptr<Sound> p_ShotSound;
	std::unique_ptr<Sound> p_ExplodeSound;
	std::unique_ptr<Sound> p_ThrustSound;
	std::unique_ptr<Shot> p_Shots[4];
	std::unique_ptr<Location> p_ExpLoc[6];
	std::vector<Entity*> p_ShipLives;


	SceneMesh *m_ShipExplosionMesh[6];
	SceneMesh *m_ShipFlameMesh;
	SceneMesh *m_ShipLivesMesh;

	void ApplyThrust(void);
	void StartExplode(void);
	void UpdateExplode(Number *elapsed);
	void ResetExplodeTimer(void);
	void ResetClearTimer(void);
	void ResetGameOverTimer(void);
	void ResetFlameTimer(void);
	bool CheckClear(void);
};
