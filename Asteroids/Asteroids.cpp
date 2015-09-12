#include "Asteroids.h"
std::shared_ptr<Player> p_Player(new Player);
std::shared_ptr<RockControl> p_Rocks(new RockControl);
std::shared_ptr<UFOControl> p_UFOs(new UFOControl);

Asteroids::Asteroids(PolycodeView *view, Core *core) : EventHandler()
{
	Random::Setup();

	pCore = core;
	m_Exit = false;
	// 	Core (int xRes, int yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel, int frameRate, int monitorIndex)
	//  Core::resizeTo 	(int xRes, int yRes);	
	p_Scene = std::shared_ptr<CollisionScene>(new CollisionScene());
	p_Scene->clearColor = Color(0.05, 0.025, 0.1, 1.0);
	p_Scene->useClearColor = true;

	p_Scene->getDefaultCamera()->setPosition(0, 0, -80);
	p_Scene->getDefaultCamera()->lookAt(Vector3(0, 0, 0));

	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYUP);

	p_Player->Setup(p_Scene);
	p_UFOs->Setup(p_Scene, p_Player);
	p_Rocks->Setup(p_Scene, p_Player, p_UFOs);
}

Asteroids::~Asteroids()
{
	
}

void Asteroids::handleEvent(Event *event)
{
	if (event->getDispatcher() == pCore->getInput())
	{
		InputEvent *inputEvent = (InputEvent*)event;

		if (event->getEventCode() == WIM_CLOSE)
		{
			m_Exit = true;
		}

		if (inputEvent->keyCode() == KEY_ESCAPE)
		{
			m_Exit = true;
		}

		if (inputEvent->keyCode() == KEY_UP || inputEvent->keyCode() == KEY_w)
		{
			if (event->getEventCode() == InputEvent::EVENT_KEYDOWN)
				p_Player->ThrustOn();
			else if (event->getEventCode() == InputEvent::EVENT_KEYUP)
				p_Player->ThrustOff();
		}

		if (inputEvent->keyCode() == KEY_LEFT || inputEvent->keyCode() == KEY_a)
		{
			if (event->getEventCode() == InputEvent::EVENT_KEYDOWN)
				p_Player->TurnLeft();
			else if (event->getEventCode() == InputEvent::EVENT_KEYUP)
				p_Player->TurnOff();
		}
		else if (inputEvent->keyCode() == KEY_RIGHT || inputEvent->keyCode() == KEY_d)
		{
			if (event->getEventCode() == InputEvent::EVENT_KEYDOWN)
				p_Player->TurnRight();
			else if (event->getEventCode() == InputEvent::EVENT_KEYUP)
				p_Player->TurnOff();
		}

		if (event->getEventCode() == InputEvent::EVENT_KEYDOWN)
		{
			if (inputEvent->keyCode() == KEY_LCTRL || inputEvent->keyCode() == KEY_SPACE)
			{
				p_Player->FireShot();
			}

			if (inputEvent->keyCode() == KEY_RCTRL)
			{
				p_Player->Hyperspace();
			}

			if (!p_Player->m_Active)
			{
				if (inputEvent->keyCode() == KEY_n)
				{
					p_Player->NewGame();
					p_UFOs->NewGame();
					p_Rocks->NewGame();
				}

				if (p_Player->p_HUD->m_NewHighScore)
				{
					if (inputEvent->keyCode() == KEY_LCTRL || inputEvent->keyCode() == KEY_SPACE)
						p_Player->p_HUD->SelectNextLetter();

					if (inputEvent->keyCode() == KEY_RIGHT || inputEvent->keyCode() == KEY_d)
						p_Player->p_HUD->SelectLetterUp();

					if (inputEvent->keyCode() == KEY_LEFT || inputEvent->keyCode() == KEY_a)
						p_Player->p_HUD->SelectLetterDown();
				}
			}
		}
	}
}

bool Asteroids::Update()
{
	Number *elapsed = 0;
	Number frameelapsed = pCore->getElapsed();
	elapsed = &frameelapsed;

	p_UFOs->Update(elapsed);

	if (m_Exit)
	{
		return false;
	}

	if (!p_Player->m_Active)
	{
		p_Player->UpdateGameOver();
	}

	return pCore->updateAndRender();
}

bool Asteroids::FixedUpdate()
{
	Number *elapsed = 0;
	Number frameelapsed = pCore->getElapsed();
	elapsed = &frameelapsed;

	if (p_Player->m_Active)
		p_Player->Update(elapsed);

	p_Player->UpdateShots(elapsed);
	p_Rocks->Update(elapsed);
	p_UFOs->FixedUpdate(elapsed);

	if (m_Exit)
	{
		return false;
	}

	return pCore->updateAndRender();
}
