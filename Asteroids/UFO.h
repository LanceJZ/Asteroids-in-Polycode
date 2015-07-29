#pragma once
#include "Location.h"
#include "Random.h"
#include "Player.h"
#include "Shot.h"

class UFO :	public Location
{
public:
	UFO();
	void Setup(CollisionScene *scene, std::shared_ptr<Player> player);
	void Update(Number *elapsed);
	void UpdateShot(Number *elapsed);
	void Spawn(int size);
	void Deactivate(void);
	Vector3 Position(void);
	SceneMesh *ShipBody(void);
	float Radius(void);
	SceneMesh *ShotMesh(void);
	float ShotRadius(void);
	bool ShotActive(void);
	void DeactivateShot(void);

	float m_RockSpeed;
	int m_Points;
	int m_Size;

private:
	SceneMesh *m_UFOShape;
	SceneMesh *shipLines;
	CollisionScene *m_Scene;
	std::shared_ptr<Player> pPlayer;
	std::unique_ptr<Shot> pShot;
	Timer *m_FireTimer;
	Timer *m_VectorTimer;

	bool m_AimedShot;
	bool m_FromRight;
	float timerFire;
	float timerFireAmount;
	float timerVector;
	float timerVectorAmount;
	float speed;

	void Enable(void);
	void ResetFireTimer(void);
	void ResetVectorTimer(void);
	void ChangeVector(void);
	void FireShot(float directionInRadians);
	void FireAimedShot(void);
	void FireRandomShot(void);
};

