#pragma once
#include "Location.h"

class Shot : public Location, Timer
{
public:
	Shot();

	void Setup(CollisionScene *scene);
	void Update(Number *elapsed);
	void Fire(Vector3 position, Vector3 velocity, float timer, bool playerShot);
	void Deactivate();
	bool CirclesIntersect(Vector3 position, float radius);
	SceneMesh *ShotMesh();

private:
	SceneMesh *m_Shot;
	CollisionScene *m_Scene;
	float timer;
	float timerAmount;
	bool m_PlayerShot;
};