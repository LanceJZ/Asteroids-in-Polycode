#include "Location.h"

Location::Location()
{
	m_Active = false;

	m_Rotation.Amount = 0;
	m_Rotation.Acceleration = 0;
	m_Rotation.Velocity = 0;

	m_Position = Polycode::Vector3();
	m_Velocity = Polycode::Vector3();
	m_Acceleration = Polycode::Vector3();

	m_WindowWidth = 1024 / (90 / 3.7);
	m_WindowHeight = 800 / (90 / 3.7);
}

//Protected methods
void Location::CheckForEdge(void)
{
	if (m_Position.x < -m_WindowWidth)
		m_Position.x = m_WindowWidth - 1;

	if (m_Position.x > m_WindowWidth)
		m_Position.x = -m_WindowWidth + 1;

	if (m_Position.y < -m_WindowHeight)
		m_Position.y = m_WindowHeight - 1;

	if (m_Position.y > m_WindowHeight)
		m_Position.y = -m_WindowHeight + 1;
}

void Location::Update(Number *elapsed)
{
	//Calculate movement this frame according to velocity and acceleration.
	m_Velocity += m_Acceleration;
	m_Position += (m_Velocity * *elapsed);
	//Calculate rotation this frame according to velocity and acceleration.
	m_Rotation.Velocity += m_Rotation.Acceleration;
	m_Rotation.Amount += (m_Rotation.Velocity * *elapsed);

	if (m_Rotation.Amount > 360)
		m_Rotation.Amount = 0;

	if (m_Rotation.Amount < 0)
		m_Rotation.Amount = 360;
}

bool Location::CirclesIntersect(Polycode::Vector3 Target, float TargetRadius)
{
	float distance = sqrt((Target.x - m_Position.x) * (Target.x - m_Position.x) +
		(Target.y - m_Position.y) * (Target.y - m_Position.y));

	if (distance < m_Radius + TargetRadius)
	{
		return true;
	}

	return false;
}