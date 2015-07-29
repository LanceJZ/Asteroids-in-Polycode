#include "Rock.h"

Rock::Rock()
{
}

void Rock::Setup(CollisionScene *scene, int size, std::shared_ptr<Player> player, std::shared_ptr<UFOControl> ufo)
{
	// There are four rock shapes.
	// Rock One size in pixels 58 (29 x 2) in the Y and 59 (28.5 x 2) in the X.
	// Point one from the top corner is at 0 x 15 y. Point two is at 14 x 0 y. Point three is at x 29 y 8. Point four is at 43 x 0 y.
	// Point five is at 59 x 15 y. point six is at 44 x 21 y. Point seven is at 59 x 36 y. Point eight is at 43 x 58 y.
	// Point nine is at 20 x 51 y. Point ten is at 0 x 44 y. Point eleven is at 8 x 29 y. There are twelve points.
	// With zero as the center the points are: Positive X is on the left of the screen.
	// Size 0 Large, 1 Med, 2 Small.

	m_RockShape = new SceneMesh(Mesh::LINE_LOOP_MESH);

	int var = Random::Clip(Random::Number(0.1, 3.9), 0, 3);

	if (var == 2)
		RockFour();
	else if (var == 1)
		RockThree();
	else if (var == 0)
		RockTwo();
	else
		RockOne();

	m_RockShape->cacheToVertexBuffer(true);
	m_RockShape->setColor(0.6, 0.6, 0.8, 0.8);

	m_Size = size;
	m_Scene = scene;
	pPlayer = player;
	pUFO = ufo;

	m_Points = 20;
	m_Radius = 3;
	m_RockSpeed = 5;

	if (m_Size == 1)
	{
		m_RockSpeed = 9.5;
		m_RockShape->Scale(Vector3(0.5, 0.5, 0.5));
		m_Points = 50;
		m_Radius = 2;
	}

	if (m_Size == 2)
	{
		m_RockSpeed = 18;
		m_RockShape->Scale(Vector3(0.25, 0.25, 0.25));
		m_Points = 100;
		m_Radius = 1;
	}
}

void Rock::RockOne(void)
{
	m_RockShape->getMesh()->addVertex(2.9, 1.5, 0.0);
	m_RockShape->getMesh()->addVertex(1.5, 3.0, 0.0);
	m_RockShape->getMesh()->addVertex(0.0, 2.2, 0.0);
	m_RockShape->getMesh()->addVertex(-1.5, 3.0, 0.0);
	m_RockShape->getMesh()->addVertex(-2.9, 1.5, 0.0);
	m_RockShape->getMesh()->addVertex(-1.5, 0.7, 0.0);
	m_RockShape->getMesh()->addVertex(-2.9, -0.7, 0.0);
	m_RockShape->getMesh()->addVertex(-1.5, -3.0, 0.0);
	m_RockShape->getMesh()->addVertex(0.7, -2.1, 0.0);
	m_RockShape->getMesh()->addVertex(1.5, -3.0, 0.0);
	m_RockShape->getMesh()->addVertex(2.9, -1.5, 0.0);
	m_RockShape->getMesh()->addVertex(2.1, 0.0, 0.0);
}

void Rock::RockTwo(void)
{
	m_RockShape->getMesh()->addVertex(2.9, 1.5, 0.0);
	m_RockShape->getMesh()->addVertex(1.4, 2.9, 0.0);
	m_RockShape->getMesh()->addVertex(0.0, 1.5, 0.0);
	m_RockShape->getMesh()->addVertex(-1.5, 2.9, 0.0);
	m_RockShape->getMesh()->addVertex(-2.9, 1.5, 0.0);
	m_RockShape->getMesh()->addVertex(-2.2, 0.0, 0.0);
	m_RockShape->getMesh()->addVertex(-2.9, -1.5, 0.0);
	m_RockShape->getMesh()->addVertex(-0.7, -2.9, 0.0);
	m_RockShape->getMesh()->addVertex(1.4, -2.9, 0.0);
	m_RockShape->getMesh()->addVertex(2.9, -1.4, 0.0);
}

void Rock::RockThree(void)
{
	m_RockShape->getMesh()->addVertex(2.9, 1.5, 0.0);
	m_RockShape->getMesh()->addVertex(0.7, 1.5, 0.0);
	m_RockShape->getMesh()->addVertex(1.6, 2.9, 0.0);
	m_RockShape->getMesh()->addVertex(-0.8, 2.9, 0.0);
	m_RockShape->getMesh()->addVertex(-2.9, 1.5, 0.0);
	m_RockShape->getMesh()->addVertex(-2.9, 0.8, 0.0);
	m_RockShape->getMesh()->addVertex(-0.8, 0.0, 0.0);
	m_RockShape->getMesh()->addVertex(-2.9, -1.4, 0.0);
	m_RockShape->getMesh()->addVertex(-1.4, -2.8, 0.0);
	m_RockShape->getMesh()->addVertex(-0.7, -2.1, 0.0);
	m_RockShape->getMesh()->addVertex(1.5, -2.9, 0.0);
	m_RockShape->getMesh()->addVertex(2.9, -0.8, 0.0);
}

void Rock::RockFour(void)
{
	m_RockShape->getMesh()->addVertex(2.9, 0.8, 0.0);
	m_RockShape->getMesh()->addVertex(0.6, 2.9, 0.0);
	m_RockShape->getMesh()->addVertex(-1.5, 2.9, 0.0);
	m_RockShape->getMesh()->addVertex(-3.0, 0.7, 0.0);
	m_RockShape->getMesh()->addVertex(-3.0, -0.7, 0.0);
	m_RockShape->getMesh()->addVertex(-1.6, -2.9, 0.0);
	m_RockShape->getMesh()->addVertex(-1.4, -2.9, 0.0);
	m_RockShape->getMesh()->addVertex(0.0, -2.9, 0.0);
	m_RockShape->getMesh()->addVertex(0.0, -0.8, 0.0);
	m_RockShape->getMesh()->addVertex(1.4, -2.8, 0.0);
	m_RockShape->getMesh()->addVertex(2.9, -0.7, 0.0);
	m_RockShape->getMesh()->addVertex(1.5, -0.0, 0.0);
}

void Rock::Spawn(Vector3 position)
{
	m_Position = position;
	Enable();
}

void Rock::Spawn(void)
{	
	m_Position.x = m_WindowWidth - 3;
	m_Position.y = Random::Number(0, m_WindowHeight * 2) - m_WindowHeight;
	Enable();
}

Vector3 Rock::Position(void)
{
	return m_Position;
}

void Rock::Update(Number *elapsed)
{
	Location::Update(elapsed);

	m_RockShape->setPosition(m_Position);
	CheckForEdge();

	if (pPlayer->m_Active)
	{
		if (CirclesIntersect(pPlayer->Position(), pPlayer->m_Radius))
		{
			CollisionResult *rockvsPlayer = &m_Scene->testCollision(m_RockShape, pPlayer->ShipBody());

			if (rockvsPlayer->collided)
			{
				pPlayer->Hit();
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (pPlayer->ShotActive(i))
		{
			if (CirclesIntersect(pPlayer->ShotMesh(i)->getPosition(), pPlayer->ShotRadius(i)))
			{
				CollisionResult *rockVsPlayerShot = &m_Scene->testCollision(m_RockShape, pPlayer->ShotMesh(i));

				if (rockVsPlayerShot->collided)
				{
					m_Hit = true;
					pPlayer->DeactivateShot(i);
					break;
				}
			}
		}
	}

	if (pUFO->Active())
	{
		if (CirclesIntersect(pUFO->Position(), pUFO->Radius()))
		{
			CollisionResult *UFOVSRock = &m_Scene->testCollision(m_RockShape, pUFO->ShipBody());

			if (UFOVSRock->collided)
			{
				m_Hit = true;
				pUFO->Deactivate();
			}
		}
	}

	if (pUFO->ShotActive())
	{
		if (CirclesIntersect(pUFO->ShotMesh()->getPosition(), pUFO->ShotRadius()))
		{
			CollisionResult *UFOVSRock = &m_Scene->testCollision(m_RockShape, pUFO->ShotMesh());

			if (UFOVSRock->collided)
			{
				m_Hit = true;
				pUFO->DeactivateShot();
			}
		}

	}
}

void Rock::Enable(void)
{
	m_Active = true;
	m_Hit = false;
	m_RockShape->setPosition(m_Position);
	m_RockShape->enabled = true;
	m_Scene->addCollisionChild(m_RockShape, CollisionEntity::SHAPE_MESH);

	float rad = Random::Number(0, (float)Pi * 2);
	float amt = Random::Number(m_RockSpeed * 0.1, m_RockSpeed);

	m_Velocity = Vector3(cos(rad) * amt, sin(rad) * amt, 0);
}

void Rock::Deactivate(void)
{
	m_Active = false;
	m_Scene->removeCollision(m_RockShape);
	m_Scene->removeEntity(m_RockShape);
	m_RockShape->enabled = false;
}