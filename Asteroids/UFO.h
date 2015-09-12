#pragma once
#include "Location.h"
#include "Random.h"
#include "Player.h"
#include "Shot.h"

class UFO :	public Location
{
public:
	UFO(void);
	void Setup(std::shared_ptr<CollisionScene> scene, std::shared_ptr<Player> player);
	void Update(Number *elapsed);
	void FixedUpdate(Number *elapsed);
	void UpdateShot(Number *elapsed);
	void Spawn(int size);
	void Deactivate(void);
	void DeactivateShot(void);
	bool ShotActive(void);
	float Radius(void);
	float ShotRadius(void);

	bool m_Hit;
	bool m_Done;
	int m_Points;
	int m_Size;

	SceneMesh *ShotMesh(void);
	SceneMesh *m_UFOMesh;

private:
	SceneMesh *shipLines;
	std::shared_ptr<CollisionScene> m_Scene;
	std::shared_ptr<Player> p_Player;
	std::unique_ptr<Shot> p_Shot;
	std::unique_ptr<Timer> p_FireTimer;
	std::unique_ptr<Timer> p_VectorTimer;
	std::unique_ptr<Sound> p_ShotSound;
	std::unique_ptr<Sound> p_ExplodeSound;
	std::unique_ptr<Sound> p_EngineLargeSound;
	std::unique_ptr<Sound> p_EngineSmallSound;

	bool m_AimedShot;
	bool m_FromRight;
	float m_FireTimerAmount;
	float m_VectorTimerAmount;
	float m_Speed;

	void Enable(void);
	void ResetFireTimer(void);
	void ResetVectorTimer(void);
	void ChangeVector(void);
	void FireShot(float directionInRadians);
	void FireAimedShot(void);
	void FireRandomShot(void);
};

