#pragma once
#include <Polycode.h>
#include "PolycodeView.h"
#include "Polycode3DPhysics.h"

struct Rotate
{
	float Amount;
	float Velocity;
	float Acceleration;
};

class Location
{
public:
	Location();

	void Update(Number *elapsed);
	bool CirclesIntersect(Polycode::Vector3 Target, float TargetRadius);
	bool m_Active;
	float m_Radius;

protected:
	const double Pi = 3.1415926535897932384626433832795;

	int m_WindowHeight;
	int m_WindowWidth;

	Polycode::Vector3 m_Position;
	Polycode::Vector3 m_Velocity;
	Polycode::Vector3 m_Acceleration;

	Rotate m_Rotation; //In Degrees

	void CheckForEdge(void);
};
