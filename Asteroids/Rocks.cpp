#include "Rocks.h"

Rocks::Rocks(void)
{
}

void Rocks::Setup(CollisionScene *scene, std::shared_ptr<Player> player, std::shared_ptr<UFOControl> ufo)
{
	m_Scene = scene;
	pPlayer = player;
	pUFO = ufo;

	NewGame();
}

void Rocks::Update(Number *elapsed)
{
	int numberOfActiveRocks = 0;
	int numberClear = 0;
	bool playerClear = false;

	for (size_t rock = 0; rock < pLargeRocks.size(); rock++)
	{
		if (pLargeRocks.at(rock)->m_Active)
		{
			pLargeRocks.at(rock)->Update(elapsed);

			if (pLargeRocks.at(rock)->m_Hit)
			{
				SpawnMedRocks(pLargeRocks.at(rock)->Position());
				pLargeRocks.at(rock)->Deactivate();				
			}

			if (pPlayer->GetHit())
			{
				playerClear = pLargeRocks.at(rock)->CheckClear();

				if (playerClear)
					numberClear++;
			}

			numberOfActiveRocks++;
		}
	}

	for (size_t rock = 0; rock < pMedRocks.size(); rock++)
	{
		if (pMedRocks.at(rock)->m_Active)
		{
			pMedRocks.at(rock)->Update(elapsed);

			if (pMedRocks.at(rock)->m_Hit)
			{
				SpawnSmallRocks(pMedRocks.at(rock)->Position());
				pMedRocks.at(rock)->Deactivate();
			}

			if (pPlayer->GetHit())
			{
				playerClear = pMedRocks.at(rock)->CheckClear();

				if (playerClear)
					numberClear++;
			}

			numberOfActiveRocks++;
		}
	}

	for (size_t rock = 0; rock < pSmallRocks.size(); rock++)
	{
		if (pSmallRocks.at(rock)->m_Active)
		{
			pSmallRocks.at(rock)->Update(elapsed);
			if (pSmallRocks.at(rock)->m_Hit)
			{
				pSmallRocks.at(rock)->Deactivate();
			}

			if (pPlayer->GetHit())
			{
				playerClear = pSmallRocks.at(rock)->CheckClear();

				if (playerClear)
					numberClear++;
			}

			numberOfActiveRocks++;
		}
	}

	if (playerClear)
	{
		if (numberClear == numberOfActiveRocks)
			pPlayer->SetClear();
	}
	
	if (numberOfActiveRocks < 1)
	{
		if (m_NumberOfRocks < 18)
			m_NumberOfRocks++;

		m_Wave++;

		pUFO->WaveNumber(m_Wave);

		SpawnNewWave(m_NumberOfRocks);
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

	m_NumberOfRocks = 10;
	m_Wave = 0;
	SpawnNewWave(m_NumberOfRocks);
}

void Rocks::CreateRocks(void)
{
}

void Rocks::ClearAllRocks(void)
{
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

void Rocks::SpawnMedRocks(Vector3 location)
{
	for (int rock = 0; rock < 2; rock++)
	{
		bool spawnnewrock = true;

		for (int rockcheck = 0; rockcheck < pMedRocks.size(); rockcheck++)
		{
			if (!pMedRocks[rockcheck]->m_Active)
			{
				spawnnewrock = false;
				pMedRocks[rockcheck]->Spawn(location);
				break;
			}
		}

		if (spawnnewrock)
		{
			pMedRocks.push_back(std::unique_ptr<Rock>(new Rock()));
			pMedRocks[pMedRocks.size() - 1]->Setup(m_Scene, 1, pPlayer, pUFO);
			pMedRocks[pMedRocks.size() - 1]->Spawn(location);
		}
	}
}

void Rocks::SpawnSmallRocks(Vector3 location)
{
	for (int rock = 0; rock < 2; rock++)
	{
		bool spawnnewrock = true;

		for (int rockcheck = 0; rockcheck < pSmallRocks.size(); rockcheck++)
		{
			if (!pSmallRocks[rockcheck]->m_Active)
			{
				spawnnewrock = false;
				pSmallRocks[rockcheck]->Spawn(location);
				break;
			}
		}

		if (spawnnewrock)
		{
			pSmallRocks.push_back(std::unique_ptr<Rock>(new Rock()));
			pSmallRocks[pSmallRocks.size() - 1]->Setup(m_Scene, 2, pPlayer, pUFO);
			pSmallRocks[pSmallRocks.size() - 1]->Spawn(location);
		}
	}
}