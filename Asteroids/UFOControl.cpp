#include "UFOControl.h"

UFOControl::UFOControl() : Timer(false, 10000)
{
	timerAmount = 10015;
	spawnCounter = 0;
	ResetTimer();
}

void UFOControl::Setup(CollisionScene * scene, std::shared_ptr<Player> player)
{
	m_Scene = scene;
	pPlayer = player;

	ResetTimer();

	pUFO = std::unique_ptr<UFO>(new UFO());
	pUFO->Setup(scene, player);
}

void UFOControl::Update(Number * elapsed)
{
	if (Timer::elapsed > timer && !pUFO->m_Active)
	{
		SpawnUFO();
		ResetTimer();
		spawnCounter++;
	}

	if (pUFO->m_Active)
	{
		pUFO->Update(elapsed);
		ResetTimer();
	}

	if (pUFO->ShotActive())
		pUFO->UpdateShot(elapsed);
}

void UFOControl::WaveNumber(int Wave)
{
	wave = Wave;
}

Vector3 UFOControl::Position(void)
{
	return pUFO->Position();
}

float UFOControl::ShotRadius(void)
{
	return pUFO->ShotRadius();
}

float UFOControl::Radius(void)
{
	return pUFO->Radius();
}

bool UFOControl::Active(void)
{
	return pUFO->m_Active;
}

SceneMesh * UFOControl::ShipBody(void)
{
	return pUFO->ShipBody();
}

void UFOControl::Deactivate(void)
{
	pUFO->Deactivate();
}

void UFOControl::DeactivateShot(void)
{
	pUFO->DeactivateShot();
}

SceneMesh * UFOControl::ShotMesh(void)
{
	return pUFO->ShotMesh();
}

bool UFOControl::ShotActive(void)
{
	return pUFO->ShotActive();
}

void UFOControl::SpawnUFO()
{
	float spawnPercent = (float)(pow(0.985, (spawnCounter + 15) / (wave + 1)));
	int size;

	if (Random::Number(1, 100) < spawnPercent * 100)
		size = 0;
	else
		size = 1;

	pUFO->Spawn(size);
}

void UFOControl::ResetTimer()
{
	timer = Random::Number(Random::Clip((timerAmount - (wave * 0.25)), timerAmount * 0.5, timerAmount * 1.15), Random::Clip((timerAmount - (wave * 0.25)),
		timerAmount * 1.15, timerAmount * 2.15));

	Timer::Reset();
	Timer::setTimerInterval(timer);
}
