#include "Shot.h"

Shot::Shot() : Timer(false, 2000)
{
}

void Shot::Update(Number *elapsed)
{
	Location::Update(elapsed);

	m_Shot->setPosition(m_Position);

	CheckForEdge();

	if (Timer::elapsed > timerAmount)
		Deactivate();
}

void Shot::Setup(CollisionScene *scene)
{
	m_Scene = scene;
	m_Shot = new SceneMesh(Mesh::LINE_MESH);
	float size = 0.095;

	m_Shot->getMesh()->addVertex(-size, 0, 0);
	m_Shot->getMesh()->addVertex(size, 0, 0);
	m_Shot->getMesh()->addVertex(0, -size, 0);
	m_Shot->getMesh()->addVertex(0, size, 0);
	m_Shot->setColor(1, 1, 1, 1);
	m_Shot->cacheToVertexBuffer(true);
	m_Shot->enabled = false;
	m_Active = false;
	m_Radius = 0.1;
}

void Shot::Fire(Vector3 position, Vector3 velocity, float timer, bool playerShot)
{
	m_Position = position;
	m_Velocity = velocity;
	m_PlayerShot = playerShot;
	m_Shot->setPosition(m_Position);
	m_Shot->enabled = true;
	m_Active = true;
	timerAmount = timer;
	m_Scene->addCollisionChild(m_Shot, CollisionEntity::SHAPE_SPHERE);
	Timer::Reset();
	Timer::setTimerInterval(timerAmount);
}

void Shot::Deactivate()
{
	m_Shot->enabled = false;
	m_Active = false;
	m_Scene->removeCollision(m_Shot);
	m_Scene->removeEntity(m_Shot);

}

bool Shot::CirclesIntersect(Vector3 position, float radius)
{
	return Location::CirclesIntersect(position, radius);
}

SceneMesh *Shot::ShotMesh()
{
	return m_Shot;
}