#pragma once
#include <memory>
#include <Polycode.h>
#include "Random.h"
#include "Player.h"
#include "RockControl.h"
#include "UFOControl.h"

class Asteroids : public EventHandler
{
public:
	Asteroids(PolycodeView *view, Core *core);
	~Asteroids();

	void handleEvent(Event *events);
	bool Update(void);
	bool FixedUpdate(void);

private:	
	Core * pCore;
	std::shared_ptr<CollisionScene> p_Scene;

	bool m_Exit;
};
