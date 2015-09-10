#pragma once
#include "Location.h"
#include "Random.h"
#include "Player.h"
#include "Shot.h"

class UFO :	public Location
{
public:
	UFO();
	void Setup(std::shared_ptr<CollisionScene> scene, std::shared_ptr<Player> player);
	void Update(Number *elapsed);
	void UpdateShot(Number *elapsed);
	void Spawn(int size);
	void Deactivate(void);
	void DeactivateShot(void);
	bool ShotActive(void);
	float Radius(void);
	float ShotRadius(void);

	float m_RockSpeed;
	int m_Points;
	int m_Size;
	bool m_Hit;
	bool m_Done;

	SceneMesh *ShotMesh(void);
	SceneMesh *m_UFOMesh;

private:
	SceneMesh *shipLines;
	std::shared_ptr<CollisionScene> m_Scene;
	std::shared_ptr<Player> pPlayer;
	std::unique_ptr<Shot> pShot;
	Timer *m_FireTimer;
	Timer *m_VectorTimer;

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

