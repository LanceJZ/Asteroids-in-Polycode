#pragma once
#include <memory>
#include <Polycode.h>
#include "PolycodeView.h"
#include "Polycode3DPhysics.h"
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
	Core *core;
	CollisionScene *scene;
};
