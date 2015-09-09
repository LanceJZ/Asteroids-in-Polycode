#pragma once
#include "Location.h"
#include <memory>

class Shot : public Location, Timer
{
public:
	Shot();

	void Setup(std::shared_ptr<CollisionScene> scene);
	void Update(Number *elapsed);
	void Fire(Vector3 position, Vector3 velocity, float timer, bool playerShot);
	void Deactivate();
	bool CirclesIntersect(Vector3 position, float radius);
	SceneMesh *m_ShotMesh;

private:
	std::shared_ptr<CollisionScene> m_Scene;
	float timer;
	float timerAmount;
	bool m_PlayerShot;
};