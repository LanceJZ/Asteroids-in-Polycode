#include "Player.h"

Player::Player()
{
	turnLeft = false;
	turnRight = false;
	thrust = false;
	hit = false;

	timerClearAmount = 2.5;
	timerExplodeAmount = 2.75;
	m_ExplodeTimer = new Timer(false, timerExplodeAmount);
	m_ClearTimer = new Timer(false, timerClearAmount);
}

void Player::Setup(CollisionScene *scene)
{
	m_Scene = scene;
	//Player original ship is 23 (11.5 x 2) pixels long, and 14 (8 x 2) pixels wide.
	//The bottom is not flat. It starts 4 pixels from the side and 4 from the bottom and goes down at an angle to the bottom corner.
	//The bottom is flat only from the upper part to the other side point 4 from the other side.
	//The points are with the front at positive X with the center at zero. Positive X is to the left of the screen.
	//The left of screen, positive X is the direction for rotation zero.
	//The top of the screen, positive Y is the direction for rotation zero.

	m_ShipBody = new SceneMesh(Mesh::LINE_LOOP_MESH);

	m_ShipBody->getMesh()->addVertex(-1.15, 0.8, 0.0); //Top back tip.
	m_ShipBody->getMesh()->addVertex(1.15, 0, 0.0); //Nose pointing to the left of screen.
	m_ShipBody->getMesh()->addVertex(-1.15, -0.8, 0.0);
	m_ShipBody->getMesh()->addVertex(-0.95, -0.4, 0.0);
	m_ShipBody->getMesh()->addVertex(-0.95, 0.4, 0.0);
	m_ShipBody->cacheToVertexBuffer(true);

	m_Radius = 1.5;

	for (int i = 0; i < 4; i++)
	{
		pShots[i] = std::unique_ptr<Shot>(new Shot());
		pShots[i]->Setup(scene);
	}
}

SceneMesh *Player::ShipBody()
{
	return m_ShipBody;
}

SceneMesh *Player::ShotMesh(int shot)
{
	return pShots[shot]->ShotMesh();
}

float Player::ShotRadius(int shot)
{
	return pShots[shot]->m_Radius;
}

void Player::Activate(void)
{
	m_Scene->addCollisionChild(m_ShipBody, CollisionEntity::SHAPE_MESH);
	m_ShipBody->enabled = true;
	m_Active = true;
}

void Player::Deactivate(void)
{
	m_Active = false;
	m_Scene->removeCollision(m_ShipBody);
	m_Scene->removeEntity(m_ShipBody);
	m_ShipBody->enabled = false;
}

void Player::NewGame(void)
{
	Reset();

	lives = 4;

	Activate();
}

void Player::Reset(void)
{
	hit = false;
	gameOver = false;
	m_Rotation.Amount = 180;
	m_Position = Vector3(0, 0, 0);
	m_Velocity = Vector3(0, 0, 0);
	m_Acceleration = Vector3(0, 0, 0);
	m_ShipBody->setColor(0.8, 0.8, 1.0, 1.0);
}

void Player::DeactivateShot(int shot)
{
	pShots[shot]->Deactivate();
}

bool Player::ShotActive(int shot)
{
	return pShots[shot]->m_Active;
}

Vector3 Player::Position()
{
	return m_Position;
}

void Player::Update(Number *elapsed)
{
	Location::Update(elapsed);

	if (!hit)
	{
		if (turnLeft)
		{
			m_Rotation.Velocity = -200;
		}
		else if (turnRight)
		{
			m_Rotation.Velocity = 200;
		}
		else
		{
			m_Rotation.Velocity = 0;
		}

		if (thrust)
		{
			ThrustOn();
		}
		else
		{
			m_Acceleration = Vector3(0, 0, 0);
		}

		m_ShipBody->setRotationEuler(Vector3(0, 0, m_Rotation.Amount));
	}
	else
	{
		Explode();

		if (m_ExplodeTimer->getElapsedf() > timerExplode)
		{
			if (gameOver)
			{
				Deactivate();
				gameOver = true;
			}
			else
				Reset();
		}
	}

	m_ShipBody->setPosition(m_Position);

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

void Player::Turn(bool left, bool right)
{
	turnRight = right;
	turnLeft = left;
}

void Player::Thrust(bool on)
{
	thrust = on;
}

void Player::Hyperspace()
{
	m_Velocity = Vector3(0, 0, 0);
	m_Position.x = Random::Number(3, m_WindowWidth * 2 - 3) - m_WindowWidth;
	m_Position.y = Random::Number(3, m_WindowHeight * 2 - 3) - m_WindowHeight;
}

void Player::Hit()
{
	if (!hit)
	{		
		lives--;
		hit = true;
		m_Velocity = m_Velocity * 0.1;
		m_Acceleration = Vector3(0, 0, 0);
		ResetExplodeTimer();

		if (lives < 1)
			gameOver = true;
	}
}

bool Player::GetHit()
{
	return hit;
}

void Player::SetLives(int numberOfLives)
{
	lives = numberOfLives;
}

void Player::ThrustOn()
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

void Player::Explode()
{
	m_ShipBody->setColor(1.0, 0.1, 0.1, 0.8);
}

void Player::ResetExplodeTimer()
{
	m_ExplodeTimer->Reset();
	m_ExplodeTimer->setTimerInterval(timerExplodeAmount);
	timerExplode = timerExplodeAmount;
}

void Player::ResetClearTimer()
{
	m_ClearTimer->Reset();
	m_ClearTimer->setTimerInterval(timerClearAmount);
	timerClear = timerClearAmount;
}

void Player::FireShot()
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