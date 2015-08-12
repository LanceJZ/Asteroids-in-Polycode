#include "UFO.h"

UFO::UFO()
{
	m_FireTimer = new Timer(false, 2000);
	m_VectorTimer = new Timer(false, 2500);
	timerVectorAmount = 3;
	timerFire = 2;
	speed = 5;

	pShot = std::unique_ptr<Shot>(new Shot());
}

void UFO::Setup(CollisionScene * scene, std::shared_ptr<Player> player)
{
	m_Scene = scene;
	pPlayer = player;
	
	//The left of screen, positive X is the direction for rotation zero.
	//The top of the screen, positive Y is the direction for rotation zero.

	m_UFOShape = new SceneMesh(Mesh::LINE_LOOP_MESH);

	m_UFOShape->getMesh()->addVertex(1.9, -0.4, 0.0); // Far left edge Bottom line
	m_UFOShape->getMesh()->addVertex(0.7, 0.4, 0.0); // Top line left edge
	m_UFOShape->getMesh()->addVertex(0.3, 1.1, 0.0);
	m_UFOShape->getMesh()->addVertex(-0.3, 1.1, 0.0);
	m_UFOShape->getMesh()->addVertex(-0.7, 0.4, 0.0); // Top line right edge
	m_UFOShape->getMesh()->addVertex(-1.9, -0.4, 0.0); // Right edge bottom line
	m_UFOShape->getMesh()->addVertex(-0.8, -1.1, 0.0);
	m_UFOShape->getMesh()->addVertex(0.8, -1.1, 0.0);
	m_UFOShape->cacheToVertexBuffer(true);
	m_UFOShape->setColor(0.7, 0.7, 0.9, 0.9);

	shipLines = new SceneMesh(Mesh::LINE_MESH);

	shipLines->getMesh()->addVertex(0.7, 0.4, 0.0); // Top line
	shipLines->getMesh()->addVertex(-0.7, 0.4, 0.0);
	shipLines->getMesh()->addVertex(1.9, -0.4, 0.0); // Bottom line
	shipLines->getMesh()->addVertex(-1.9, -0.4, 0.0);
	shipLines->cacheToVertexBuffer(true);
	shipLines->setColor(0.7, 0.7, 0.9, 0.9);

	pShot->Setup(scene);
}

void UFO::Update(Number * elapsed)
{
	Location::Update(elapsed);

	if (m_FireTimer->getElapsedf() > timerFire)
	{
		if (!pShot->m_Active)
		{
			if (m_AimedShot && pPlayer->m_Active)
			{
				float var = Random::Number(0, 10);

				if (var < 7.5)
				{
					FireAimedShot();
				}
				else
				{
					FireRandomShot();
				}
			}
			else
			{
				FireRandomShot();
			}
		}
	}

	if (m_VectorTimer->getElapsedf() > timerVector)
	{
		ChangeVector();
	}

	m_UFOShape->setPosition(m_Position);

	if (m_Position.x > m_WindowWidth || m_Position.x < -m_WindowWidth)
	{
		Deactivate();
	}

	CheckForEdge();

	if (CirclesIntersect(pPlayer->Position(), pPlayer->m_Radius))
	{
		CollisionResult *vsPlayer = &m_Scene->testCollision(m_UFOShape, pPlayer->ShipBody());

		if (vsPlayer->collided)
		{
			pPlayer->Hit();
			pPlayer->GotPoints(m_Points);
			Deactivate();
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (pPlayer->ShotActive(i))
		{
			if (CirclesIntersect(pPlayer->ShotMesh(i)->getPosition(), pPlayer->ShotRadius(i)))
			{
				CollisionResult *rockVsPlayerShot = &m_Scene->testCollision(m_UFOShape, pPlayer->ShotMesh(i));

				if (rockVsPlayerShot->collided)
				{
					Deactivate();
					pPlayer->DeactivateShot(i);
					pPlayer->GotPoints(m_Points);
					break;
				}
			}
		}
	}
}

void UFO::UpdateShot(Number * elapsed)
{
	pShot->Update(elapsed);

	if (pShot->CirclesIntersect(pPlayer->Position(), pPlayer->m_Radius))
	{
		CollisionResult *shotvsPlayer = &m_Scene->testCollision(pShot->ShotMesh(), pPlayer->ShipBody());

		if (shotvsPlayer->collided)
		{
			pPlayer->Hit();
		}
	}
}

void UFO::Spawn(int size)
{
	float var = Random::Number(0, 10);

	if (var > 5)
	{
		m_Position.x = -m_WindowWidth;
		m_Velocity.x = speed;
	}
	else
	{
		m_Position.x = m_WindowWidth;
		m_Velocity.x = -speed;
	}

	m_Position.y = Random::Number(0, m_WindowHeight * 2) - m_WindowHeight;

	Enable();

	if (size == 0)
	{
		m_AimedShot = false;
		m_Points = 200;
		m_Radius = 2;
		m_UFOShape->setScale(Vector3(1, 1, 1));
	}
	else if (size == 1)
	{
		m_AimedShot = true;
		m_Points = 1000;
		m_Radius = 1;
		m_UFOShape->setScale(Vector3(0.5, 0.5, 0.5));
	}

	ChangeVector();
}

Vector3 UFO::Position(void)
{
	return m_Position;
}

float UFO::ShotRadius(void)
{
	return pShot->m_Radius;
}

bool UFO::ShotActive(void)
{
	return pShot->m_Active;
}

void UFO::DeactivateShot(void)
{
	pShot->Deactivate();
}

SceneMesh * UFO::ShipBody(void)
{
	return m_UFOShape;
}

SceneMesh * UFO::ShotMesh(void)
{
	return pShot->ShotMesh();
}

float UFO::Radius(void)
{
	return m_Radius;
}

void UFO::Enable(void)
{
	m_Scene->addCollisionChild(m_UFOShape, CollisionEntity::SHAPE_MESH);
	m_UFOShape->addChild(shipLines);
	m_UFOShape->setPosition(m_Position);
	m_UFOShape->enabled = true;
	m_Active = true;
	ResetFireTimer();
}

void UFO::ResetFireTimer(void)
{
	m_FireTimer->Reset();
	m_FireTimer->setTimerInterval(timerFireAmount);
	timerFire = timerFireAmount;
}

void UFO::ResetVectorTimer(void)
{
	m_VectorTimer->Reset();
	m_VectorTimer->setTimerInterval(timerVectorAmount);
	timerVector = timerVectorAmount;
}

void UFO::ChangeVector(void)
{
	// if going strait go up or down. If not going strait go strait.

	float var = Random::Number(0, 10);

	if (var < 5)
	{
		if (m_Velocity.y == 0 && var < 2.5)
			m_Velocity.y = speed;
		else if (m_Velocity.y == 0)
			m_Velocity.y = -speed;
		else
			m_Velocity.y = 0;
	}

	ResetVectorTimer();
}

void UFO::FireShot(float directionInRadians)
{
	pShot->Fire(Vector3(cos(directionInRadians) * 1.9, sin(directionInRadians) * 1.9, 0) + m_Position,
		Vector3(cos(directionInRadians) * 30, sin(directionInRadians) * 30, 0) + m_Velocity * 0.5, 1300, false);

	ResetFireTimer();
}

void UFO::FireAimedShot(void)
{
	FireShot(atan2(pPlayer->Position().y - m_Position.y, pPlayer->Position().x - m_Position.x));
}

void UFO::FireRandomShot(void)
{
	FireShot(Random::Number(0, (float)Pi * 2));
}

void UFO::Deactivate(void)
{
	m_UFOShape->enabled = false;
	m_Scene->removeCollision(m_UFOShape);
	m_Scene->removeEntity(m_UFOShape);
	m_Active = false;
}