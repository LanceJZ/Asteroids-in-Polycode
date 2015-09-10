#include "Asteroids.h"

std::shared_ptr<Player> pPlayer(new Player);
std::shared_ptr<RockControl> pRocks(new RockControl);
std::shared_ptr<UFOControl> pUFOs(new UFOControl);

Asteroids::Asteroids(PolycodeView *view)
{
	Random::Setup();
	// 	Core (int xRes, int yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel, int frameRate, int monitorIndex)
	//  Core::resizeTo 	(int xRes, int yRes);	
	core = std::unique_ptr<Core>(new POLYCODE_CORE(view, 800, 720, false, true, 0, 0, 120, 0, true));
	scene = std::shared_ptr<CollisionScene>(new CollisionScene());
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
	core->Shutdown();
}

void Asteroids::handleEvent(Event *event)
{
	if (event->getDispatcher() == core->getInput())
	{
		InputEvent *inputEvent = (InputEvent*)event;

		if (inputEvent->keyCode() == KEY_UP || inputEvent->keyCode() == KEY_w)
		{
			if (event->getEventCode() == InputEvent::EVENT_KEYDOWN)
				pPlayer->ThrustOn();
			else if (event->getEventCode() == InputEvent::EVENT_KEYUP)
				pPlayer->ThrustOff();
		}

		if (inputEvent->keyCode() == KEY_LEFT || inputEvent->keyCode() == KEY_a)
		{
			if (event->getEventCode() == InputEvent::EVENT_KEYDOWN)
				pPlayer->TurnLeft();
			else if (event->getEventCode() == InputEvent::EVENT_KEYUP)
				pPlayer->TurnOff();
		}
		else if (inputEvent->keyCode() == KEY_RIGHT || inputEvent->keyCode() == KEY_d)
		{
			if (event->getEventCode() == InputEvent::EVENT_KEYDOWN)
				pPlayer->TurnRight();
			else if (event->getEventCode() == InputEvent::EVENT_KEYUP)
				pPlayer->TurnOff();
		}

		if (event->getEventCode() == InputEvent::EVENT_KEYDOWN)
		{
			if (inputEvent->keyCode() == KEY_LCTRL || inputEvent->keyCode() == KEY_SPACE)
			{
				pPlayer->FireShot();
			}

			if (inputEvent->keyCode() == KEY_RCTRL)
			{
				pPlayer->Hyperspace();
			}

			if (!pPlayer->m_Active)
			{
				if (inputEvent->keyCode() == KEY_n)
				{
					pUFOs->NewGame();
					pRocks->NewGame();
					pPlayer->NewGame();
				}

				if (pPlayer->p_HUD->m_NewHighScore)
				{
					if (inputEvent->keyCode() == KEY_LCTRL || inputEvent->keyCode() == KEY_SPACE)
						pPlayer->p_HUD->SelectNextLetter();

					if (inputEvent->keyCode() == KEY_RIGHT || inputEvent->keyCode() == KEY_d)
						pPlayer->p_HUD->SelectLetterUp();

					if (inputEvent->keyCode() == KEY_LEFT || inputEvent->keyCode() == KEY_a)
						pPlayer->p_HUD->SelectLetterDown();
				}
			}
		}
	}
}

bool Asteroids::Update()
{
	Number *elapsed = 0;
	Number frameelapsed = core->getElapsed();
	elapsed = &frameelapsed;

	if (pPlayer->m_Active)
		pPlayer->Update(elapsed);
	else
	{
		pPlayer->UpdateGameOver();
	}

	pPlayer->UpdateShots(elapsed);

	pRocks->Update(elapsed);
	pUFOs->Update(elapsed);

	return core->updateAndRender();
}