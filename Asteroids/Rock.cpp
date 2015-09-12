#include "Rock.h"

Rock::Rock()
{
}

void Rock::Setup(std::shared_ptr<CollisionScene> scene, int size, std::shared_ptr<Player> player, std::shared_ptr<UFOControl> ufo)
{
	// There are four rock shapes.
	// Rock One size in pixels 58 (29 x 2) in the Y and 59 (28.5 x 2) in the X.
	// Point one from the top corner is at 0 x 15 y. Point two is at 14 x 0 y. Point three is at x 29 y 8. Point four is at 43 x 0 y.
	// Point five is at 59 x 15 y. point six is at 44 x 21 y. Point seven is at 59 x 36 y. Point eight is at 43 x 58 y.
	// Point nine is at 20 x 51 y. Point ten is at 0 x 44 y. Point eleven is at 8 x 29 y. There are twelve points.
	// With zero as the center the points are: Positive X is on the left of the screen.
	// Size 0 Large, 1 Med, 2 Small.

	m_RockMesh = new SceneMesh(Mesh::LINE_LOOP_MESH);

	int rockType = Random::Clip(Random::Number(0.1, 3.9), 0, 3);

	if (rockType == 2)
		RockFour();
	else if (rockType == 1)
		RockThree();
	else if (rockType == 0)
		RockTwo();
	else
		RockOne();

	m_RockMesh->cacheToVertexBuffer(true);
	m_RockMesh->setColor(0.6, 0.6, 0.8, 0.8);
	m_RockMesh->lineSmooth = true;

	m_Size = size;
	p_Scene = scene;
	p_Player = player;
	p_UFO = ufo;

	m_Points = 20;
	m_RockSpeed = 6;

	m_Radius = 6.5f;


	if (m_Size == 1)
	{
		m_RockSpeed = 10;
		m_RockMesh->Scale(Vector3(0.5, 0.5, 0.5));
		m_Points = 50;
		m_Radius = 4.5f;
	}

	if (m_Size == 2)
	{
		m_RockSpeed = 30;
		m_RockMesh->Scale(Vector3(0.25, 0.25, 0.25));
		m_Points = 100;
		m_Radius = 2.5f;
	}

	// Sound ---------
	p_ExplodeSound = std::unique_ptr<Sound>(new Sound("audio/RockExplosion.wav"));
	p_ExplodeSound->setVolume(0.05);
	p_ExplodeSound->setPitch(0.75);
}

void Rock::RockOne(void)
{
	m_RockMesh->getMesh()->addVertex(2.9, 1.5, 0.0);
	m_RockMesh->getMesh()->addVertex(1.5, 3.0, 0.0);
	m_RockMesh->getMesh()->addVertex(0.0, 2.2, 0.0);
	m_RockMesh->getMesh()->addVertex(-1.5, 3.0, 0.0);
	m_RockMesh->getMesh()->addVertex(-2.9, 1.5, 0.0);
	m_RockMesh->getMesh()->addVertex(-1.5, 0.7, 0.0);
	m_RockMesh->getMesh()->addVertex(-2.9, -0.7, 0.0);
	m_RockMesh->getMesh()->addVertex(-1.5, -3.0, 0.0);
	m_RockMesh->getMesh()->addVertex(0.7, -2.1, 0.0);
	m_RockMesh->getMesh()->addVertex(1.5, -3.0, 0.0);
	m_RockMesh->getMesh()->addVertex(2.9, -1.5, 0.0);
	m_RockMesh->getMesh()->addVertex(2.1, 0.0, 0.0);
}

void Rock::RockTwo(void)
{
	m_RockMesh->getMesh()->addVertex(2.9, 1.5, 0.0);
	m_RockMesh->getMesh()->addVertex(1.4, 2.9, 0.0);
	m_RockMesh->getMesh()->addVertex(0.0, 1.5, 0.0);
	m_RockMesh->getMesh()->addVertex(-1.5, 2.9, 0.0);
	m_RockMesh->getMesh()->addVertex(-2.9, 1.5, 0.0);
	m_RockMesh->getMesh()->addVertex(-2.2, 0.0, 0.0);
	m_RockMesh->getMesh()->addVertex(-2.9, -1.5, 0.0);
	m_RockMesh->getMesh()->addVertex(-0.7, -2.9, 0.0);
	m_RockMesh->getMesh()->addVertex(1.4, -2.9, 0.0);
	m_RockMesh->getMesh()->addVertex(2.9, -1.4, 0.0);
}

void Rock::RockThree(void)
{
	m_RockMesh->getMesh()->addVertex(2.9, 1.5, 0.0);
	m_RockMesh->getMesh()->addVertex(0.7, 1.5, 0.0);
	m_RockMesh->getMesh()->addVertex(1.6, 2.9, 0.0);
	m_RockMesh->getMesh()->addVertex(-0.8, 2.9, 0.0);
	m_RockMesh->getMesh()->addVertex(-2.9, 1.5, 0.0);
	m_RockMesh->getMesh()->addVertex(-2.9, 0.8, 0.0);
	m_RockMesh->getMesh()->addVertex(-0.8, 0.0, 0.0);
	m_RockMesh->getMesh()->addVertex(-2.9, -1.4, 0.0);
	m_RockMesh->getMesh()->addVertex(-1.4, -2.8, 0.0);
	m_RockMesh->getMesh()->addVertex(-0.7, -2.1, 0.0);
	m_RockMesh->getMesh()->addVertex(1.5, -2.9, 0.0);
	m_RockMesh->getMesh()->addVertex(2.9, -0.8, 0.0);
}

void Rock::RockFour(void)
{
	m_RockMesh->getMesh()->addVertex(2.9, 0.8, 0.0);
	m_RockMesh->getMesh()->addVertex(0.6, 2.9, 0.0);
	m_RockMesh->getMesh()->addVertex(-1.5, 2.9, 0.0);
	m_RockMesh->getMesh()->addVertex(-3.0, 0.7, 0.0);
	m_RockMesh->getMesh()->addVertex(-3.0, -0.7, 0.0);
	m_RockMesh->getMesh()->addVertex(-1.6, -2.9, 0.0);
	m_RockMesh->getMesh()->addVertex(-1.4, -2.9, 0.0);
	m_RockMesh->getMesh()->addVertex(0.0, -2.9, 0.0);
	m_RockMesh->getMesh()->addVertex(0.0, -0.8, 0.0);
	m_RockMesh->getMesh()->addVertex(1.4, -2.8, 0.0);
	m_RockMesh->getMesh()->addVertex(2.9, -0.7, 0.0);
	m_RockMesh->getMesh()->addVertex(1.5, -0.0, 0.0);
}

void Rock::Spawn(Vector3 position)
{
	m_Position = position;
	Enable();
}

void Rock::Spawn(void)
{	
	m_Position.x = m_WindowWidth;
	m_Position.y = Random::Number(0, m_WindowHeight * 2) - m_WindowHeight;
	Enable();
}

bool Rock::PlayerNotClear(void)
{
	if (m_Active)
		return CirclesIntersect(Vector3(0, 0, 0), 12);
	else
		return false;
}

void Rock::Update(Number *elapsed)
{
	Location::Update(elapsed);

	if (!m_Hit)
	{
		m_RockMesh->setPosition(m_Position);
		CheckForEdge();

		if (p_Player->m_Active && !p_Player->m_Hit)
		{
			if (CirclesIntersect(p_Player->Position(), p_Player->m_Radius))
			{
				CollisionResult *rockvsPlayer = &p_Scene->testCollision(m_RockMesh, p_Player->m_ShipMesh);

				if (rockvsPlayer->collided)
				{
					p_Player->Hit();
					p_Player->GotPoints(m_Points);
					m_Hit = true;
				}
			}
		}

		for (int i = 0; i < 4; i++)
		{
			if (p_Player->ShotActive(i))
			{
				if (CirclesIntersect(p_Player->ShotMesh(i)->getPosition(), p_Player->ShotRadius(i)))
				{
					CollisionResult *rockVsPlayerShot = &p_Scene->testCollision(m_RockMesh, p_Player->ShotMesh(i));

					if (rockVsPlayerShot->collided)
					{
						m_Hit = true;
						p_Player->DeactivateShot(i);
						p_Player->GotPoints(m_Points);
						break;
					}
				}
			}
		}

		if (p_UFO->Active())
		{
			if (CirclesIntersect(p_UFO->Position(), p_UFO->Radius()))
			{
				CollisionResult *UFOVSRock = &p_Scene->testCollision(m_RockMesh, p_UFO->ShipBody());

				if (UFOVSRock->collided)
				{
					m_Hit = true;
					p_UFO->HitRock();
				}
			}
		}

		if (p_UFO->ShotActive())
		{
			if (CirclesIntersect(p_UFO->ShotMesh()->getPosition(), p_UFO->ShotRadius()))
			{
				CollisionResult *UFOVSRock = &p_Scene->testCollision(m_RockMesh, p_UFO->ShotMesh());

				if (UFOVSRock->collided)
				{
					m_Hit = true;
					p_UFO->DeactivateShot();
					
				}
			}
		}

		if (m_Hit && !p_Player->m_GameOver)
		{
			if (p_ExplodeSound != NULL)
				p_ExplodeSound->Play();
		}
	}
}

void Rock::Enable(void)
{
	m_Active = true;
	m_Hit = false;
	m_RockMesh->setPosition(m_Position);
	m_RockMesh->enabled = true;
	p_Scene->addCollisionChild(m_RockMesh, CollisionEntity::SHAPE_MESH);

	float rad = Random::Number(0, (float)Pi * 2);
	float amt = Random::Number(m_RockSpeed * 0.1, m_RockSpeed);

	m_Velocity = Vector3(cos(rad) * amt, sin(rad) * amt, 0);
}

void Rock::Deactivate(void)
{
	m_Active = false;
	p_Scene->removeCollision(m_RockMesh);
	p_Scene->removeEntity(m_RockMesh);
	m_RockMesh->enabled = false;
}