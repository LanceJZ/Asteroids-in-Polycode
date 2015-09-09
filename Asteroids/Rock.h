#pragma once
#include "Location.h"
#include "Random.h"
#include "Player.h"
#include "UFOControl.h"

class Rock : public Location
{
public:
	Rock();

	void Setup(std::shared_ptr<CollisionScene> scene, int size, std::shared_ptr<Player> player, std::shared_ptr<UFOControl> ufo);
	void RockOne(void);
	void RockTwo(void);
	void RockThree(void);
	void RockFour(void);
	void Spawn(Vector3 position);
	void Spawn(void);
	void Update(Number *elapsed);
	void Deactivate(void);
	bool PlayerNotClear(void);

	float m_RockSpeed;
	int m_Points;
	int m_Size;
	bool m_Hit;

private:
	std::shared_ptr<CollisionScene> m_Scene;
	std::shared_ptr<Player> pPlayer;
	std::shared_ptr<UFOControl> pUFO;

	SceneMesh *m_RockMesh;

	void Enable(void);
};
