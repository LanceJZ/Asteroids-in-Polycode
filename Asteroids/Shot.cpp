#include "Shot.h"

Shot::Shot() : Timer(false, 2000)
{
}

void Shot::Update(Number *elapsed)
{
	Location::Update(elapsed);

	m_ShotMesh->setPosition(m_Position);

	CheckForEdge();

	if (Timer::elapsed > timerAmount)
		Deactivate();
}

void Shot::Setup(std::shared_ptr<CollisionScene> scene)
{
	m_Scene = scene;
	m_ShotMesh = new SceneMesh(Mesh::LINE_MESH);
	float size = 0.095;

	m_ShotMesh->getMesh()->addVertex(-size, 0, 0);
	m_ShotMesh->getMesh()->addVertex(size, 0, 0);
	m_ShotMesh->getMesh()->addVertex(0, -size, 0);
	m_ShotMesh->getMesh()->addVertex(0, size, 0);
	m_ShotMesh->cacheToVertexBuffer(true);
	m_ShotMesh->setColor(1, 1, 1, 1);
	m_ShotMesh->enabled = false;
	m_Active = false;
	m_Radius = 1.5f;
}

void Shot::Fire(Vector3 position, Vector3 velocity, float timer, bool playerShot)
{
	m_Position = position;
	m_Velocity = velocity;
	m_PlayerShot = playerShot;
	m_ShotMesh->setPosition(m_Position);
	m_ShotMesh->enabled = true;
	m_Active = true;
	timerAmount = timer;
	m_Scene->addCollisionChild(m_ShotMesh, CollisionEntity::SHAPE_SPHERE);
	Timer::Reset();
	Timer::setTimerInterval(timerAmount);
}

void Shot::Deactivate()
{
	m_ShotMesh->enabled = false;
	m_Active = false;
	m_Scene->removeCollision(m_ShotMesh);
	m_Scene->removeEntity(m_ShotMesh);

}

bool Shot::CirclesIntersect(Vector3 position, float radius)
{
	return Location::CirclesIntersect(position, radius);
}