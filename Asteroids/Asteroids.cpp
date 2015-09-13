#include "Asteroids.h"
std::shared_ptr<Player> p_Player(new Player);
std::shared_ptr<RockControl> p_Rocks(new RockControl);
std::shared_ptr<UFOControl> p_UFOs(new UFOControl);

Asteroids::Asteroids(PolycodeView *view, Core *core) : EventHandler()
{
	Random::Setup();

	pCore = core;
	m_Exit = false;
	m_Paused = false;
	m_FiredShot = false;
	m_Hyper = false;
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

		if (inputEvent->keyCode() == KEY_ESCAPE)
		{
			m_Exit = true;
		}

		if (event->getEventCode() == InputEvent::EVENT_KEYDOWN)
		{
			if (!p_Player->m_Active)
			{
				if (inputEvent->keyCode() == KEY_n || inputEvent->keyCode() == KEY_RETURN)
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
			else
			{
				if (inputEvent->keyCode() == KEY_p)
				{
					if (m_Paused)
						m_Paused = false;
					else
						m_Paused = true;

					p_UFOs->Pause(m_Paused);
					p_Rocks->Pause(m_Paused);
					p_Player->Pause(m_Paused);
				}
			}
		}
	}
}

void Asteroids::handlePlayerInput(void)
{
	bool key_up = pCore->getInput()->getKeyState(KEY_UP);
	bool key_left = pCore->getInput()->getKeyState(KEY_LEFT);
	bool key_right = pCore->getInput()->getKeyState(KEY_RIGHT);
	bool key_lctrl = pCore->getInput()->getKeyState(KEY_LCTRL);
	bool key_rctrl = pCore->getInput()->getKeyState(KEY_RCTRL);

	bool key_w = pCore->getInput()->getKeyState(KEY_w);
	bool key_a = pCore->getInput()->getKeyState(KEY_a);
	bool key_d = pCore->getInput()->getKeyState(KEY_d);
	bool key_space = pCore->getInput()->getKeyState(KEY_SPACE);

	if (key_up || key_w)
	{
		p_Player->ThrustOn();
	}
	else
	{
		p_Player->ThrustOff();
	}
	
	if (key_left || key_a || key_right || key_d)
	{
		if (key_left || key_a)
			p_Player->TurnLeft();

		if (key_right || key_d)
			p_Player->TurnRight();
	}
	else
	{
		p_Player->TurnOff();
	}

	if (key_lctrl || key_space)
	{
		if (!m_FiredShot)
		{
			p_Player->FireShot();
			m_FiredShot = true;
		}
	}
	else
	{
		m_FiredShot = false;
	}

	if (key_rctrl)
	{
		if (!m_Hyper)
		{
			p_Player->Hyperspace();
			m_Hyper = true;
		}
		else
		{
			m_Hyper = false;
		}
	}
}

bool Asteroids::Update()
{
	if (!m_Paused)
	{
		Number *elapsed = 0;
		Number frameelapsed = pCore->getElapsed();
		elapsed = &frameelapsed;

		if (p_Player->m_Active)
		{
			p_Player->Update(elapsed);
			handlePlayerInput();
		}
		else
		{
			p_Player->UpdateGameOver();
		}

		p_Player->UpdateShots(elapsed);
		p_Rocks->Update(elapsed);
		p_UFOs->Update(elapsed);
	}

	if (m_Exit)
	{
		return false;
	}

	return pCore->updateAndRender();
}