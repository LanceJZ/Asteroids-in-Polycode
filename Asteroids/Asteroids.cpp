#include "Asteroids.h"

std::shared_ptr<Player> pPlayer(new Player);
std::shared_ptr<Rocks> pRocks(new Rocks);
std::shared_ptr<UFOControl> pUFOs(new UFOControl);

Asteroids::Asteroids(PolycodeView *view)
{
	Random::Setup();
	// 	Core (int xRes, int yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel, int frameRate, int monitorIndex)
	//  Core::resizeTo 	(int xRes, int yRes);	
	core = new POLYCODE_CORE(view, 1024, 720, false, true, 6, 1, 60, 0, true);
	scene = new CollisionScene();
	scene->clearColor = Color(0.05, 0.025, 0.1, 1.0);
	scene->useClearColor = true;

	scene->getDefaultCamera()->setPosition(0, 0, -80);
	scene->getDefaultCamera()->lookAt(Vector3(0, 0, 0));

	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYUP);

	pPlayer->Setup(scene);
	pUFOs->Setup(scene, pPlayer);
	pRocks->Setup(scene, pPlayer, pUFOs);
}

Asteroids::~Asteroids()
{
}

void Asteroids::handleEvent(Event *event)
{
	if (event->getDispatcher() == core->getInput())
	{
		InputEvent *inputEvent = (InputEvent*)event;

		if (event->getEventCode() == InputEvent::EVENT_KEYDOWN)
		{
			if (inputEvent->keyCode() == KEY_UP)
				pPlayer->Thrust(true);

			if (inputEvent->keyCode() == KEY_LEFT)
				pPlayer->Turn(true, false);
			else if (inputEvent->keyCode() == KEY_RIGHT)
				pPlayer->Turn(false, true);

			if (inputEvent->keyCode() == KEY_LCTRL)
			{
				pPlayer->FireShot();
			}

			if (inputEvent->keyCode() == KEY_RCTRL)
			{
				pPlayer->Hyperspace();
			}

			if (inputEvent->keyCode() == KEY_n && !pPlayer->m_Active)
			{
				pUFOs->Deactivate();
				pUFOs->DeactivateShot();
				pRocks->NewGame();
				pPlayer->NewGame();
			}
		}
		else if (event->getEventCode() == InputEvent::EVENT_KEYUP)
		{
			if (inputEvent->keyCode() == KEY_UP)
				pPlayer->Thrust(false);

			if (inputEvent->keyCode() == KEY_LEFT || inputEvent->keyCode() == KEY_RIGHT)
				pPlayer->Turn(false, false);
		}
	}
}

bool Asteroids::Update()
{
	Number elapsed = core->getElapsed();

	if (pPlayer->m_Active)
		pPlayer->Update(&elapsed);

	pPlayer->UpdateShots(&elapsed);

	pRocks->Update(&elapsed);
	pUFOs->Update(&elapsed);

	return core->updateAndRender();
}