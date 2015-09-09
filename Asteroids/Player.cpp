#include "Player.h"

Player::Player(void)
{
	hit = false;
	gameOver = true;
	gameOverDisplay = 1;

	timerClearAmount = 2.5;
	timerExplodeAmount = 2.75;
	timerGameOverAmount = 6.66f;
	m_ExplodeTimer = std::unique_ptr<Timer>(new Timer(false, timerExplodeAmount));
	m_ClearTimer = std::unique_ptr<Timer>(new Timer(false, timerClearAmount));
	m_GameOverTimer = std::unique_ptr<Timer>(new Timer(false, timerGameOverAmount));
}

void Player::Setup(std::shared_ptr<CollisionScene> scene)
{
	m_Scene = scene;
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
		pShots[i] = std::unique_ptr<Shot>(new Shot());
		pShots[i]->Setup(scene);
	}

	pHUD = std::unique_ptr<HUD>(new HUD());
	pHUD->Setup(scene);

	ResetGameOverTimer();
}

float Player::ShotRadius(int shot)
{
	return pShots[shot]->m_Radius;
}

void Player::Activate(void)
{
	m_Scene->addCollisionChild(m_ShipMesh, CollisionEntity::SHAPE_MESH);
	m_ShipMesh->enabled = true;
	m_Active = true;
	gameOver = false;
	hit = false;
	thrustOn = false;
}

void Player::Deactivate(void)
{
	m_Active = false;
	m_Scene->removeCollision(m_ShipMesh);
	m_Scene->removeEntity(m_ShipMesh);
	m_ShipMesh->enabled = false;
}

void Player::NewGame(void)
{
	Reset();
	Activate();
	pHUD->NewGame();
	pHUD->Add(0);

	Vector3 livesPos = Vector3(m_WindowWidth - 4, m_WindowHeight + -5, 0);

	for (int i = 0; i < pHUD->Lives(); i++)
	{
		m_ShipLives.push_back(m_ShipMesh->Clone(true, false));
		m_ShipLives.at(m_ShipLives.size() - 1)->setColor(1.0, 1.0, 1.0, 0.95);
		m_ShipLives.at(m_ShipLives.size() - 1)->setPosition(livesPos);
		m_ShipLives.at(m_ShipLives.size() - 1)->setRotationEuler(Vector3(0, 0, 90));
		m_Scene->addChild(m_ShipLives.at(m_ShipLives.size() - 1));
		livesPos.x -= 2;
	}
}

void Player::Reset(void)
{
	hit = false;
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
	pShots[shot]->Deactivate();
}

bool Player::ShotActive(int shot)
{
	return pShots[shot]->m_Active;
}

Vector3 Player::Position(void)
{
	return m_Position;
}

Vector3 Player::ShotPosition(int shot)
{
	return pShots[shot]->m_Position;
}

SceneMesh *Player::ShotMesh(int shot)
{
	return pShots[shot]->m_ShotMesh;
}

void Player::Update(Number *elapsed)
{
	Location::Update(elapsed);

	if (hit)
	{
		Explode();

		if (m_ExplodeTimer->getElapsedf() > timerExplodeAmount)
		{
			if (gameOver)
			{
				Deactivate();
				pHUD->GameOver();
			}
			else if (clearToSpawn)
				Reset();
			else if (!clearToSpawn)
				m_ShipMesh->enabled = false;
		}
	}
	else
	{
		if (thrustOn)
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
		if (pShots[i]->m_Active)
			pShots[i]->Update(elapsed);
	}
}

void Player::UpdateGameOver(void)
{
	if (!pHUD->m_NewHighScore)
	{
		if (m_GameOverTimer->getElapsedf() > timerGameOverAmount)
		{
			ResetGameOverTimer();
			pHUD->DisplayHighScores(gameOverDisplay, true);

			if (gameOverDisplay == 0)
				gameOverDisplay = 1;
			else
				gameOverDisplay = 0;

		}
	}
}

void Player::TurnLeft(void)
{

	if (!hit)
		m_Rotation.Velocity = -200;
	else
		m_Rotation.Velocity = 0;
}

void Player::TurnRight(void)
{
	if (!hit)
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
	m_Velocity = Vector3(0, 0, 0);
	m_Position.x = Random::Number(3, m_WindowWidth * 2 - 3) - m_WindowWidth;
	m_Position.y = Random::Number(3, m_WindowHeight * 2 - 3) - m_WindowHeight;
}

void Player::Hit(void)
{
	if (!hit)
	{
		pHUD->LostLife();
		hit = true;
		clearToSpawn = false;
		m_Velocity = m_Velocity * 0.1;
		m_Acceleration = 0;
		m_Rotation.Velocity = 0;
		ResetExplodeTimer();

		if (pHUD->Lives() < 1)
		{
			gameOver = true;
		}
	}

	UpdateLivesDisplay();
}

void Player::UpdateLivesDisplay(void)
{
	for (size_t i = 0; i < m_ShipLives.size(); i++)
	{
		m_Scene->removeEntity(m_ShipLives.at(i));
	}

	m_ShipLives.clear();

	Vector3 livesPos = Vector3(m_WindowWidth - 4, m_WindowHeight + -5, 0);

	for (int i = 0; i < pHUD->Lives(); i++)
	{
		m_ShipLives.push_back(m_ShipMesh->Clone(true, false));
		m_ShipLives.at(m_ShipLives.size() - 1)->setColor(1.0, 1.0, 1.0, 0.95);
		m_ShipLives.at(m_ShipLives.size() - 1)->setPosition(livesPos);
		m_ShipLives.at(m_ShipLives.size() - 1)->setRotationEuler(Vector3(0, 0, 90));
		m_Scene->addChild(m_ShipLives.at(m_ShipLives.size() - 1));
		livesPos.x -= 2;
	}
}

void Player::GotPoints(int points)
{
	pHUD->Add(points);

	UpdateLivesDisplay();
}

bool Player::GotHit(void)
{
	return hit;
}

void Player::SetClear(void)
{
	clearToSpawn = true;
}

bool Player::CheckClear(void)
{
	return false;
}

void Player::ThrustOn(void)
{
	thrustOn = true;
}

void Player::ThrustOff(void)
{
	thrustOn = false;
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
	m_ExplodeTimer->Reset();
	m_ExplodeTimer->setTimerInterval(timerExplodeAmount);
}

void Player::ResetClearTimer(void)
{
	m_ClearTimer->Reset();
	m_ClearTimer->setTimerInterval(timerClearAmount);
}

void Player::ResetGameOverTimer(void)
{
	m_GameOverTimer->Reset();
	m_GameOverTimer->setTimerInterval(timerGameOverAmount);
}

void Player::FireShot(void)
{
	if (!hit)
	{
		for (int i = 0; i < 4; i++)
		{
			if (!pShots[i]->m_Active)
			{
				float rad = (m_Rotation.Amount) * Pi / 180.0;
				Vector3 direction = Vector3(cos(rad) * 40, sin(rad) * 40, 0);
				Vector3 position = Vector3(cos(rad) * 1.15, sin(rad) * 1.15, 0);

				pShots[i]->Fire(position + m_Position, direction + m_Velocity * 0.5, 1500, true);
				break;
			}
		}
	}
}