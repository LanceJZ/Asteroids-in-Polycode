#include "Player.h"

Player::Player(void)
{
	m_Hit = false;
	m_GameOver = true;
	m_GameOverDisplay = 1;

	m_TimerClearAmount = 2.5;
	m_TimerExplodeAmount = 2.75;
	m_TimerGameOverAmount = 6.66f;
	p_ExplodeTimer = std::unique_ptr<Timer>(new Timer(false, m_TimerExplodeAmount));
	p_ClearTimer = std::unique_ptr<Timer>(new Timer(false, m_TimerClearAmount));
	p_GameOverTimer = std::unique_ptr<Timer>(new Timer(false, m_TimerGameOverAmount));
}

void Player::Setup(std::shared_ptr<CollisionScene> scene)
{
	p_Scene = scene;
	//Player original ship is 23 (11.5 x 2) pixels long, and 14 (8 x 2) pixels wide.
	//The bottom is not flat. It starts 4 pixels from the side and 4 from the bottom and goes down at an angle to the bottom corner.
	//The bottom is flat only from the upper part to the other side point 4 from the other side.
	//The points are with the front at positive X with the center at zero. Positive X is to the left of the screen.
	//The left of screen, positive X is the direction for rotation zero.
	//The top of the screen, positive Y is the direction for rotation zero.

	m_ShipMesh = new SceneMesh(Mesh::LINE_LOOP_MESH);

	m_ShipMesh->getMesh()->addVertex(-1.15, 0.8, 0.0); //Top back tip.
	m_ShipMesh->getMesh()->addVertex(1.15, 0, 0.0); //Nose pointing to the left of screen.
	m_ShipMesh->getMesh()->addVertex(-1.15, -0.8, 0.0); //Bottom back tip.
	m_ShipMesh->getMesh()->addVertex(-0.95, -0.4, 0.0); //Bottom inside back.
	m_ShipMesh->getMesh()->addVertex(-0.95, 0.4, 0.0); //Top inside back.
	m_ShipMesh->cacheToVertexBuffer(true);
	m_ShipMesh->lineSmooth = true;

	m_Radius = 1.5;

	for (int i = 0; i < 4; i++)
	{
		p_Shots[i] = std::unique_ptr<Shot>(new Shot());
		p_Shots[i]->Setup(scene);
	}

	p_HUD = std::unique_ptr<HUD>(new HUD());
	p_HUD->Setup(scene);

	ResetGameOverTimer();
}

float Player::ShotRadius(int shot)
{
	return p_Shots[shot]->m_Radius;
}

void Player::Activate(void)
{
	p_Scene->addCollisionChild(m_ShipMesh, CollisionEntity::SHAPE_MESH);
	m_ShipMesh->enabled = true;
	m_Active = true;
	m_GameOver = false;
	m_Hit = false;
	m_ThrustOn = false;
}

void Player::Deactivate(void)
{
	m_Active = false;
	p_Scene->removeCollision(m_ShipMesh);
	p_Scene->removeEntity(m_ShipMesh);
	m_ShipMesh->enabled = false;
}

void Player::NewGame(void)
{
	Reset();
	Activate();
	p_HUD->NewGame();
	p_HUD->Add(0);

	Vector3 livesPos = Vector3(m_WindowWidth - 4, m_WindowHeight + -5, 0);

	for (int i = 0; i < p_HUD->Lives(); i++)
	{
		p_ShipLives.push_back(m_ShipMesh->Clone(true, false));
		p_ShipLives.at(p_ShipLives.size() - 1)->setColor(1.0, 1.0, 1.0, 0.95);
		p_ShipLives.at(p_ShipLives.size() - 1)->setPosition(livesPos);
		p_ShipLives.at(p_ShipLives.size() - 1)->setRotationEuler(Vector3(0, 0, 90));
		p_Scene->addChild(p_ShipLives.at(p_ShipLives.size() - 1));
		livesPos.x -= 2;
	}
}

void Player::Reset(void)
{
	m_Hit = false;
	m_Rotation.Amount = 180;
	m_ShipMesh->setRotationEuler(Vector3(0, 0, m_Rotation.Amount));
	m_Position = Vector3(0, 0, 0);
	m_Velocity = Vector3(0, 0, 0);
	m_Acceleration = Vector3(0, 0, 0);
	m_ShipMesh->setColor(0.8, 0.8, 1.0, 1.0);
	m_ShipMesh->enabled = true;
}

void Player::DeactivateShot(int shot)
{
	p_Shots[shot]->Deactivate();
}

bool Player::ShotActive(int shot)
{
	return p_Shots[shot]->m_Active;
}

Vector3 Player::Position(void)
{
	return m_Position;
}

Vector3 Player::ShotPosition(int shot)
{
	return p_Shots[shot]->m_Position;
}

SceneMesh *Player::ShotMesh(int shot)
{
	return p_Shots[shot]->m_ShotMesh;
}

void Player::Update(Number *elapsed)
{
	Location::Update(elapsed);

	if (m_Hit)
	{
		Explode();

		if (p_ExplodeTimer->getElapsedf() > m_TimerExplodeAmount)
		{
			if (m_GameOver)
			{
				Deactivate();
				p_HUD->GameOver();
			}
			else if (m_ClearToSpawn)
				Reset();
			else if (!m_ClearToSpawn)
				m_ShipMesh->enabled = false;
		}
	}
	else
	{
		if (m_ThrustOn)
			ApplyThrust();
		else
			m_Acceleration = 0;
	}

	m_ShipMesh->setPosition(m_Position);
	m_ShipMesh->setRotationEuler(Vector3(0, 0, m_Rotation.Amount));

	CheckForEdge();
}

void Player::UpdateShots(Number * elapsed)
{
	for (int i = 0; i < 4; i++)
	{
		if (p_Shots[i]->m_Active)
			p_Shots[i]->Update(elapsed);
	}
}

void Player::UpdateGameOver(void)
{
	if (!p_HUD->m_NewHighScore)
	{
		if (p_GameOverTimer->getElapsedf() > m_TimerGameOverAmount)
		{
			ResetGameOverTimer();
			p_HUD->DisplayHighScores(m_GameOverDisplay, true);

			if (m_GameOverDisplay == 0)
				m_GameOverDisplay = 1;
			else
				m_GameOverDisplay = 0;

		}
	}
}

void Player::TurnLeft(void)
{

	if (!m_Hit)
		m_Rotation.Velocity = -200;
	else
		m_Rotation.Velocity = 0;
}

void Player::TurnRight(void)
{
	if (!m_Hit)
		m_Rotation.Velocity = 200;
	else
		m_Rotation.Velocity = 0;
}

void Player::TurnOff(void)
{
	m_Rotation.Velocity = 0;
}

void Player::Hyperspace(void)
{
	if (!m_Hit)
	{
		m_Velocity = Vector3(0, 0, 0);
		m_Position.x = Random::Number(3, m_WindowWidth * 2 - 3) - m_WindowWidth;
		m_Position.y = Random::Number(3, m_WindowHeight * 2 - 3) - m_WindowHeight;
	}
}

void Player::Hit(void)
{
	if (!m_Hit)
	{
		p_HUD->LostLife();
		m_Hit = true;
		m_ClearToSpawn = false;
		m_Velocity = m_Velocity * 0.1;
		m_Acceleration = 0;
		m_Rotation.Velocity = 0;
		ResetExplodeTimer();

		if (p_HUD->Lives() < 1)
		{
			m_GameOver = true;
		}
	}

	UpdateLivesDisplay();
}

void Player::UpdateLivesDisplay(void)
{
	for (size_t i = 0; i < p_ShipLives.size(); i++)
	{
		p_Scene->removeEntity(p_ShipLives.at(i));
	}

	p_ShipLives.clear();

	Vector3 livesPos = Vector3(m_WindowWidth - 4, m_WindowHeight + -5, 0);

	for (int i = 0; i < p_HUD->Lives(); i++)
	{
		p_ShipLives.push_back(m_ShipMesh->Clone(true, false));
		p_ShipLives.at(p_ShipLives.size() - 1)->setColor(1.0, 1.0, 1.0, 0.95);
		p_ShipLives.at(p_ShipLives.size() - 1)->setPosition(livesPos);
		p_ShipLives.at(p_ShipLives.size() - 1)->setRotationEuler(Vector3(0, 0, 90));
		p_Scene->addChild(p_ShipLives.at(p_ShipLives.size() - 1));
		livesPos.x -= 2;
	}
}

void Player::GotPoints(int points)
{
	p_HUD->Add(points);

	UpdateLivesDisplay();
}

bool Player::GotHit(void)
{
	return m_Hit;
}

void Player::SetClear(void)
{
	m_ClearToSpawn = true;
}

bool Player::CheckClear(void)
{
	return false;
}

void Player::ThrustOn(void)
{
	m_ThrustOn = true;
}

void Player::ThrustOff(void)
{
	m_ThrustOn = false;
}

void Player::ApplyThrust(void)
{
	float rad = (m_Rotation.Amount) * Pi / 180.0;

	m_Acceleration = Vector3(cos(rad) * 0.25, sin(rad) * 0.25, 0);

	float maxSp = 50;

	if (m_Velocity.x > maxSp)
		m_Velocity.x = maxSp;

	if (m_Velocity.x < -maxSp)
		m_Velocity.x = -maxSp;

	if (m_Velocity.y > maxSp)
		m_Velocity.y = maxSp;

	if (m_Velocity.y < -maxSp)
		m_Velocity.y = -maxSp;
}

void Player::Explode(void)
{
	m_ShipMesh->setColor(1.0, 0.1, 0.1, 0.8);
}

void Player::ResetExplodeTimer(void)
{
	p_ExplodeTimer->Reset();
	p_ExplodeTimer->setTimerInterval(m_TimerExplodeAmount);
}

void Player::ResetClearTimer(void)
{
	p_ClearTimer->Reset();
	p_ClearTimer->setTimerInterval(m_TimerClearAmount);
}

void Player::ResetGameOverTimer(void)
{
	p_GameOverTimer->Reset();
	p_GameOverTimer->setTimerInterval(m_TimerGameOverAmount);
}

void Player::FireShot(void)
{
	if (!m_Hit)
	{
		for (int i = 0; i < 4; i++)
		{
			if (!p_Shots[i]->m_Active)
			{
				float rad = (m_Rotation.Amount) * Pi / 180.0;
				Vector3 direction = Vector3(cos(rad) * 40, sin(rad) * 40, 0);
				Vector3 position = Vector3(cos(rad) * 1.15, sin(rad) * 1.15, 0);

				p_Shots[i]->Fire(position + m_Position, direction + m_Velocity * 0.5, 1500, true);
				break;
			}
		}
	}
}