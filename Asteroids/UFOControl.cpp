#include "UFOControl.h"

UFOControl::UFOControl() : Timer(false, 10000)
{
	timerAmount = 10015;
	spawnCounter = 0;
	ResetTimer();
}

void UFOControl::Setup(std::shared_ptr<CollisionScene> scene, std::shared_ptr<Player> player)
{
	m_Scene = scene;
	pPlayer = player;

	ResetTimer();

	pUFO = std::unique_ptr<UFO>(new UFO());
	pUFO->Setup(scene, player);
}

void UFOControl::Update(Number * elapsed)
{
	if (pUFO->m_Active)
	{
		pUFO->Update(elapsed);
	}

	if (!pUFO->m_Active)
	{
		if (Timer::elapsed > timer && !pUFO->m_Active)
		{
			SpawnUFO();
			ResetTimer();
			spawnCounter++;
		}
	}


	for (int i = 0; i < pExplosions.size(); i++)
	{
		if (pExplosions[i]->m_Active)
		{
			pExplosions[i]->Update(elapsed);
		}
	}
}

void UFOControl::FixedUpdate(Number * elapsed)
{
	if (pUFO->ShotActive())
		pUFO->UpdateShot(elapsed);

	if (pUFO->m_Active)
	{
		pUFO->FixedUpdate(elapsed);

		if (pUFO->m_Hit)
		{
			SpawnExplosion(pUFO->m_Position, pUFO->m_Radius);
			pUFO->Deactivate();
			ResetTimer();
		}

		if (pUFO->m_Done)
		{
			pUFO->Deactivate();
			ResetTimer();
		}
	}

}

void UFOControl::WaveNumber(int Wave)
{
	wave = Wave;
}

void UFOControl::HitRock(void)
{
	ResetTimer();
	Deactivate();
}

Vector3 UFOControl::Position(void)
{
	return pUFO->m_Position;
}

float UFOControl::ShotRadius(void)
{
	return pUFO->ShotRadius();
}

float UFOControl::Radius(void)
{
	return pUFO->m_Radius;
}

bool UFOControl::Active(void)
{
	return pUFO->m_Active;
}

SceneMesh * UFOControl::ShipBody(void)
{
	return pUFO->m_UFOMesh;
}

void UFOControl::Deactivate(void)
{
	pUFO->Deactivate();
}

void UFOControl::DeactivateShot(void)
{
	pUFO->DeactivateShot();
}

void UFOControl::NewGame(void)
{
	ResetTimer();
	Deactivate();
	DeactivateShot();
	spawnCounter = 0;
	wave = 0;
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
	float spawnPercent = (float)(pow(0.915, (spawnCounter * 2) / ((wave * 2) + 1)));
	int size;

	// Size 0 is the large one.
	if (Random::Number(0, 99) < spawnPercent * 100)
		size = 0;
	else
		size = 1;

	pUFO->Spawn(size);
}

void UFOControl::SpawnExplosion(Vector3 position, float size)
{
	bool spawnExp = true;

	for (int expCheck = 0; expCheck < pExplosions.size(); expCheck++)
	{
		if (!pExplosions[expCheck]->m_Active)
		{
			spawnExp = false;
			pExplosions[expCheck]->Activate(position, size);
			break;
		}
	}

	if (spawnExp)
	{
		pExplosions.push_back(std::unique_ptr<Explosion>(new Explosion()));
		pExplosions[pExplosions.size() - 1]->Setup(m_Scene);
		pExplosions[pExplosions.size() - 1]->Activate(position, size);
	}
}

void UFOControl::ResetTimer()
{
	timer = Random::Number(Random::Clip((timerAmount - (wave * 0.25)), timerAmount * 0.5, timerAmount * 1.15), Random::Clip((timerAmount - (wave * 0.25)),
		timerAmount * 1.15, timerAmount * 2.15));

	Timer::Reset();
	Timer::setTimerInterval(timer);
}
