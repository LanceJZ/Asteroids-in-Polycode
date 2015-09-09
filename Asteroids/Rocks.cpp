#include "Rocks.h"

Rocks::Rocks(void)
{
}

void Rocks::Setup(std::shared_ptr<CollisionScene> scene, std::shared_ptr<Player> player, std::shared_ptr<UFOControl> ufo)
{
	m_Scene = scene;
	pPlayer = player;
	pUFO = ufo;

	NewGame();

	for (int i = 0; i < 4; i++)
	{
		pExplosions.push_back(std::unique_ptr<Explosion>(new Explosion()));
		pExplosions[pExplosions.size() - 1]->Setup(m_Scene);
	}
}

void Rocks::Update(Number *elapsed)
{
	RockCount lRC = UpdateLargeRocks(elapsed, 0, true);

	RockCount mRC = UpdateMedRocks(elapsed, lRC.numberActive, lRC.playerAllClear);

	RockCount rocksCounted = UpdateSmallRocks(elapsed, mRC.numberActive, mRC.playerAllClear);

	if (rocksCounted.playerAllClear && !pUFO->ShotActive())
	{
		pPlayer->SetClear();
	}
	
	if (rocksCounted.numberActive < 1)
	{
		if (m_NumberOfRocks < 18)
			m_NumberOfRocks++;

		m_Wave++;

		pUFO->WaveNumber(m_Wave);

		SpawnNewWave(m_NumberOfRocks);
	}

	for (int i = 0; i < pExplosions.size(); i++)
	{
		if (pExplosions[i]->m_Active)
		{
			pExplosions[i]->Update(elapsed);
		}
	}
}

void Rocks::NewGame(void)
{
	for (size_t rock = 0; rock < pLargeRocks.size(); rock++)
	{
		pLargeRocks.at(rock)->Deactivate();
	}

	for (size_t rock = 0; rock < pMedRocks.size(); rock++)
	{
		pMedRocks.at(rock)->Deactivate();
	}

	for (size_t rock = 0; rock < pSmallRocks.size(); rock++)
	{
		pSmallRocks.at(rock)->Deactivate();
	}

	for (size_t exp = 0; exp < pExplosions.size(); exp++)
	{
		pExplosions.at(exp)->Deactivate();
	}

	m_NumberOfRocks = 4;
	m_Wave = 0;
	SpawnNewWave(m_NumberOfRocks);
}

RockCount Rocks::UpdateSmallRocks(Number * elapsed, int numberActive, bool clear)
{
	RockCount rocks;
	rocks.playerAllClear = clear;
	rocks.numberActive = numberActive;

	for (size_t rock = 0; rock < pSmallRocks.size(); rock++)
	{
		if (pSmallRocks.at(rock)->m_Active)
		{
			pSmallRocks.at(rock)->Update(elapsed);

			if (pSmallRocks.at(rock)->m_Hit)
			{
				SpawnExplosion(pSmallRocks.at(rock)->m_Position, pSmallRocks.at(rock)->m_Radius / 2);
				pSmallRocks.at(rock)->Deactivate();
			}

			rocks.numberActive++;
		}
	}

	if (pPlayer->GotHit())
	{
		if (rocks.playerAllClear)
		{
			for (size_t rock = 0; rock < pSmallRocks.size(); rock++)
			{
				if (pSmallRocks.at(rock)->PlayerNotClear())
				{
					rocks.playerAllClear = false;
					break;
				}
			}
		}
	}

	return rocks;
}

RockCount Rocks::UpdateMedRocks(Number * elapsed, int numberActive, bool clear)
{
	RockCount rocks;
	rocks.playerAllClear = clear;
	rocks.numberActive = numberActive;

	for (size_t rock = 0; rock < pMedRocks.size(); rock++)
	{
		if (pMedRocks.at(rock)->m_Active)
		{
			pMedRocks.at(rock)->Update(elapsed);

			if (pMedRocks.at(rock)->m_Hit)
			{
				SpawnSmallRocks(pMedRocks.at(rock)->m_Position);
				SpawnExplosion(pMedRocks.at(rock)->m_Position, pMedRocks.at(rock)->m_Radius / 2);
				pMedRocks.at(rock)->Deactivate();
			}

			rocks.numberActive++;
		}
	}

	if (pPlayer->GotHit())
	{
		if (rocks.playerAllClear)
		{
			for (size_t rock = 0; rock < pMedRocks.size(); rock++)
			{
				if (pMedRocks.at(rock)->PlayerNotClear())
				{
					rocks.playerAllClear = false;
					break;
				}
			}
		}
	}

	return rocks;
}

RockCount Rocks::UpdateLargeRocks(Number * elapsed, int numberActive, bool clear)
{
	RockCount rocks;
	rocks.playerAllClear = clear;
	rocks.numberActive = numberActive;

	for (size_t rock = 0; rock < pLargeRocks.size(); rock++)
	{
		if (pLargeRocks.at(rock)->m_Active)
		{
			pLargeRocks.at(rock)->Update(elapsed);

			if (pLargeRocks.at(rock)->m_Hit)
			{
				SpawnMedRocks(pLargeRocks.at(rock)->m_Position);
				SpawnExplosion(pLargeRocks.at(rock)->m_Position, pLargeRocks.at(rock)->m_Radius / 2);
				pLargeRocks.at(rock)->Deactivate();
			}

			rocks.numberActive++;
		}
	}

	if (pPlayer->GotHit())
	{
		if (rocks.playerAllClear)
		{
			for (size_t rock = 0; rock < pLargeRocks.size(); rock++)
			{
				if (pLargeRocks.at(rock)->PlayerNotClear())
				{
					rocks.playerAllClear = false;
					break;
				}
			}
		}
	}

	return rocks;
}

void Rocks::CreateRocks(void)
{
}

void Rocks::ClearAllRocks(void)
{
}

void Rocks::SpawnExplosion(Vector3 position, float size)
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

void Rocks::SpawnNewWave(int NumberOfRocks)
{
	for (int rock = 0; rock < NumberOfRocks; rock++)
	{
		bool spawnnewrock = true;

		for (int rockcheck = 0; rockcheck < pLargeRocks.size(); rockcheck++)
		{
			if (!pLargeRocks[rockcheck]->m_Active)
			{
				spawnnewrock = false;
				pLargeRocks[rockcheck]->Spawn();
				break;
			}
		}

		if (spawnnewrock)
		{
			pLargeRocks.push_back(std::unique_ptr<Rock>(new Rock()));
			pLargeRocks[pLargeRocks.size() - 1]->Setup(m_Scene, 0, pPlayer, pUFO);
			pLargeRocks[pLargeRocks.size() - 1]->Spawn();
		}
	}
}

void Rocks::SpawnMedRocks(Vector3 position)
{
	for (int rock = 0; rock < 2; rock++)
	{
		bool spawnnewrock = true;

		for (int rockcheck = 0; rockcheck < pMedRocks.size(); rockcheck++)
		{
			if (!pMedRocks[rockcheck]->m_Active)
			{
				spawnnewrock = false;
				pMedRocks[rockcheck]->Spawn(position);
				break;
			}
		}

		if (spawnnewrock)
		{
			pMedRocks.push_back(std::unique_ptr<Rock>(new Rock()));
			pMedRocks[pMedRocks.size() - 1]->Setup(m_Scene, 1, pPlayer, pUFO);
			pMedRocks[pMedRocks.size() - 1]->Spawn(position);
		}
	}
}

void Rocks::SpawnSmallRocks(Vector3 position)
{
	for (int rock = 0; rock < 2; rock++)
	{
		bool spawnnewrock = true;

		for (int rockcheck = 0; rockcheck < pSmallRocks.size(); rockcheck++)
		{
			if (!pSmallRocks[rockcheck]->m_Active)
			{
				spawnnewrock = false;
				pSmallRocks[rockcheck]->Spawn(position);
				break;
			}
		}

		if (spawnnewrock)
		{
			pSmallRocks.push_back(std::unique_ptr<Rock>(new Rock()));
			pSmallRocks[pSmallRocks.size() - 1]->Setup(m_Scene, 2, pPlayer, pUFO);
			pSmallRocks[pSmallRocks.size() - 1]->Spawn(position);
		}
	}
}