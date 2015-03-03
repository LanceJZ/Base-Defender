#include "EnemyCitySpawner.h"

void EnemyCitySpawner::Update(sf::Time *delta)
{
	for (size_t ship = 0; ship < mAngreifers.size(); ship++)
	{
		mAngreifers.at(ship)->Update(delta);
	}

	for (size_t ship = 0; ship < mAngreiferFCs.size(); ship++)
	{
		mAngreiferFCs.at(ship)->Update(delta);

		if (mAngreiferFCs.at(ship)->InPositionToBombCity() && mAngreiferFCs.at(ship)->GetActive())
		{
			SpawnAngriff_auf_Stadt(*mAngreiferFCs.at(ship)->GetPosition(), *mAngreiferFCs.at(ship)->GetVelocity(), mAngreiferFCs.at(ship)->GetCityNumber(), mAngreiferFCs.at(ship)->GetCityTarget());
			mAngreiferFCs.at(ship)->SetActive(false);
		}
	}

	for (size_t ship = 0; ship < mAngriff_auf_Stadts.size(); ship++)
	{
		mAngriff_auf_Stadts.at(ship)->Update(delta);
	}

	if (mAngreiferSpawnTimer < Common::mClock.getElapsedTime().asSeconds())
	{
		SpawnAngreifers();
		mAngreiferSpawnTimer = ResetTimer(mAngreiferSpawnTimerAmount / 1.80f, mAngreiferSpawnTimerAmount, mAngreiferSpawnTimerAmount / 4.0f);
	}

	if (mAngreifers.size() > 0)
	{
		if (mCityHuntTimer < Common::mClock.getElapsedTime().asSeconds())
		{
			SendAngreiferToCity();
			mCityHuntTimer = ResetTimer(mCityHuntTimerAmount / 1.80f, mCityHuntTimerAmount + mAngreiferFCs.size(), mCityHuntTimerAmount / 4.0f);
		}
	}
}

void EnemyCitySpawner::Draw(sf::RenderWindow *window)
{
	for (size_t ship = 0; ship < mAngreifers.size(); ship++)
	{
		mAngreifers.at(ship)->Draw(window);
	}

	for (size_t ship = 0; ship < mAngreiferFCs.size(); ship++)
	{
		mAngreiferFCs.at(ship)->Draw(window);
	}

	for (size_t ship = 0; ship < mAngriff_auf_Stadts.size(); ship++)
	{
		mAngriff_auf_Stadts.at(ship)->Draw(window);
	}
}

void EnemyCitySpawner::DrawOtherSide(sf::RenderWindow *window)
{
	for (size_t ship = 0; ship < mAngreifers.size(); ship++)
	{
		mAngreifers.at(ship)->DrawOtherSide(window);
	}

	for (size_t ship = 0; ship < mAngreiferFCs.size(); ship++)
	{
		mAngreiferFCs.at(ship)->DrawOtherSide(window);
	}

	for (size_t ship = 0; ship < mAngriff_auf_Stadts.size(); ship++)
	{
		mAngriff_auf_Stadts.at(ship)->DrawOtherSide(window);
	}
}

void EnemyCitySpawner::Initialize(sf::Texture *angreiferTexture, sf::Texture *angreiferShotTexture, sf::Texture *stadt_AngreiferTexture,
	sf::Texture *angreiferFCTexture, sf::Texture *bombTexture, sf::Texture *bombExplosion,
	sf::Vector2u windowSize, sf::Vector2f worldBounds)
{
	mWindowSize = windowSize;
	mWorldSize = worldBounds;
	mAngreiferTexture = angreiferTexture;
	mAngreiferShotTexture = angreiferShotTexture;
	mStadt_AngreiferTexture = stadt_AngreiferTexture;
	mAngreiferFCTexture = angreiferFCTexture;
	mBombTexture = bombTexture;
	mBombExplosion = bombExplosion;

	mNumberOfAngreifers = 6;
	mAngreiferSpawnTimerAmount = 230;
	mAngreiferSpawnTimer = ResetTimer(mAngreiferSpawnTimerAmount / 1.50f, mAngreiferSpawnTimerAmount, mAngreiferSpawnTimerAmount / 4.0f);
	mCityHuntTimerAmount = 15;
	mCityHuntTimer = ResetTimer(mCityHuntTimerAmount / 1.50f, mCityHuntTimerAmount, mCityHuntTimerAmount / 4.0f);

	SpawnAngreifers();
}

void EnemyCitySpawner::PlayerPointer(std::shared_ptr<Player> playerSP)
{
	pPlayer = playerSP;
}

void EnemyCitySpawner::CityPointer(std::shared_ptr<Cities> citySP)
{
	pCities = citySP;
}

void EnemyCitySpawner::SpawnAngreifers(void)
{
	for (int ship = 0; ship < mNumberOfAngreifers; ship++)
	{
		bool spawnNewShip = true;
		int spawnShip = 0;

		for (size_t ship = 0; ship < mAngreifers.size(); ship++)
		{
			if (!mAngreifers.at(ship)->GetActive())
			{
				spawnNewShip = false;
				spawnShip = ship;
				break;
			}
		}

		if (spawnNewShip)
		{
			mAngreifers.push_back(std::unique_ptr<Angreifer>(new Angreifer()));
			spawnShip = mAngreifers.size() - 1;
			mAngreifers.at(spawnShip)->Initialize(mAngreiferTexture, mAngreiferShotTexture, mWindowSize, mWorldSize);
			mAngreifers.at(spawnShip)->PlayerPointer(pPlayer);
		}

		float height = float((rand() % 10) + 20);
		float width = float(rand() % int(mWorldSize.x));
		mAngreifers.at(spawnShip)->Setup(sf::Vector2f(width, height), sf::Vector2f(float((rand() % 10) - 5), 1.0f));
	}

}

EnemyCitySpawner::EnemyCitySpawner(void)
{
}

void EnemyCitySpawner::SendAngreiferToCity(void)
{
	int liveShips = 0;
	int ofShips = 0;

	for (size_t ship = 0; ship < mAngreifers.size(); ship++)
	{
		if (mAngreifers.at(ship)->GetActive())
			liveShips++;
	}

	int sendShip = (rand() % liveShips);

	for (size_t ship = 0; ship < mAngreifers.size(); ship++)
	{
		if (mAngreifers.at(ship)->GetActive())
			ofShips++;

		if (sendShip == ofShips)
		{
			if (mAngreifers.at(ship)->GetActive())
			{
				SpawnmAngreiferFC(*mAngreifers.at(ship)->GetPosition(), *mAngreifers.at(ship)->GetVelocity());
				mAngreifers.at(ship)->SetActive(false);
			}

			break;
		}
	}
}

void EnemyCitySpawner::SpawnmAngreiferFC(sf::Vector2f position, sf::Vector2f velocity)
{
	bool spawnNewShip = true;
	int spawnShip = 0;
	int cityNumber = 0;
	sf::Vector2f cityPosition;

	for (size_t ship = 0; ship < mAngreiferFCs.size(); ship++)
	{
		if (!mAngreiferFCs.at(ship)->GetActive())
		{
			spawnNewShip = false;
			spawnShip = ship;
			break;
		}
	}

	if (spawnNewShip)
	{
		mAngreiferFCs.push_back(std::unique_ptr<AngreiferFoundCity>(new AngreiferFoundCity()));
		spawnShip = mAngreiferFCs.size() - 1;
		mAngreiferFCs.at(spawnShip)->Initialize(mAngreiferFCTexture, mAngreiferShotTexture, mWindowSize, mWorldSize);
		mAngreiferFCs.at(spawnShip)->PlayerPointer(pPlayer);
		mAngreiferFCs.at(spawnShip)->CityPointer(pCities);
	}

	cityNumber = int((position.x + 0.49f + float(mWorldSize.x / 8)) / float(mWorldSize.x / 4)) - 1;

	if (cityNumber < 0)
		cityNumber = 0;
	else if (cityNumber > 3)
		cityNumber = 3;

	cityPosition = sf::Vector2f(pCities->CityCollusion(cityNumber).left + 20 + float(rand() % int(pCities->CityCollusion(cityNumber).width - 20)),
	pCities->CityCollusion(cityNumber).top - float(rand() % int(30.0f)) + 20.0f);

	mAngreiferFCs.at(spawnShip)->Setup(position, velocity, cityNumber, cityPosition);
}

void EnemyCitySpawner::SpawnAngriff_auf_Stadt(sf::Vector2f postion, sf::Vector2f velocity, int cityAttacking, sf::Vector2f cityPosition)
{
	bool spawnNewShip = true;
	int spawnShip = 0;

	for (size_t ship = 0; ship < mAngriff_auf_Stadts.size(); ship++)
	{
		if (!mAngriff_auf_Stadts.at(ship)->GetActive())
		{
			spawnNewShip = false;
			spawnShip = ship;
			break;
		}
	}

	if (spawnNewShip)
	{
		mAngriff_auf_Stadts.push_back(std::unique_ptr<Angriff_auf_Stadt>(new Angriff_auf_Stadt()));
		spawnShip = mAngriff_auf_Stadts.size() - 1;
		mAngriff_auf_Stadts.at(spawnShip)->Initialize(mStadt_AngreiferTexture, mAngreiferShotTexture, mBombTexture, mBombExplosion, mWindowSize, mWorldSize);
		mAngriff_auf_Stadts.at(spawnShip)->PlayerPointer(pPlayer);
		mAngriff_auf_Stadts.at(spawnShip)->CityPointer(pCities);
	}

	mAngriff_auf_Stadts.at(spawnShip)->Setup(postion, velocity, cityAttacking, cityPosition);
}