#pragma once
#include <memory>
#include <Polycode.h>
#include "Random.h"
#include "Player.h"
#include "Rocks.h"
#include "UFOControl.h"

class Asteroids : public EventHandler
{
public:
	Asteroids(PolycodeView *view);
	~Asteroids();

	void handleEvent(Event *events);
	bool Update();

private:
	//std::unique_ptr<HUD> pHUD;
	std::unique_ptr<Core> core;
	std::shared_ptr<CollisionScene> scene;
};
