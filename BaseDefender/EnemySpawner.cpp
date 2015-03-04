#include "EnemySpawner.h"

void EnemySpawner::Update(sf::Time *delta)
{
	for (size_t ship = 0; ship < mMinenlegers.size(); ship++)
	{
		mMinenlegers.at(ship)->Update(delta);
	}

	for (size_t ship = 0; ship < mUnters.size(); ship++)
	{
		IsUnterHit(ship);
		mUnters.at(ship)->Update(delta);
	}

	for (size_t ship = 0; ship < mSchwärmes.size(); ship++)
	{
		mSchwärmes.at(ship)->Update(delta);
	}

	EnemyCitySpawner::Update(delta);
}

void EnemySpawner::Draw(sf::RenderWindow *window)
{
	for (size_t ship = 0; ship < mMinenlegers.size(); ship++)
	{
		mMinenlegers.at(ship)->Draw(window);
	}

	for (size_t ship = 0; ship < mUnters.size(); ship++)
	{
		mUnters.at(ship)->Draw(window);
	}

	for (size_t ship = 0; ship < mSchwärmes.size(); ship++)
	{
		mSchwärmes.at(ship)->Draw(window);
	}

	EnemyCitySpawner::Draw(window);
}

void EnemySpawner::DrawOtherSide(sf::RenderWindow *window)
{
	for (size_t ship = 0; ship < mMinenlegers.size(); ship++)
	{
		mMinenlegers.at(ship)->DrawOtherSide(window);
	}

	for (size_t ship = 0; ship < mUnters.size(); ship++)
	{
		mUnters.at(ship)->DrawOtherSide(window);
	}

	for (size_t ship = 0; ship < mSchwärmes.size(); ship++)
	{
		mSchwärmes.at(ship)->DrawOtherSide(window);
	}

	EnemyCitySpawner::DrawOtherSide(window);
}

void EnemySpawner::Initialize(sf::Texture *angreiferTexture, sf::Texture *angreiferShotTexture, sf::Texture *stadt_AngreiferTexture,
	sf::Texture *angreiferTextureFC, sf::Texture *bombTexture, sf::Texture *bombExplosion, sf::Texture *minenlegerTexture,
	sf::Texture *mineTexture, sf::Texture *unterTexture, sf::Texture *schwärmeTexture, sf::Texture *enemyExplosion,
	sf::Vector2u windowSize, sf::Vector2f worldBounds)
{
	mWindowSize = windowSize;
	mWorldSize = worldBounds;
	mMinenlegerTexture = minenlegerTexture;
	mMineTexture = mineTexture;
	mUnterTexture = unterTexture;
	mSchwärmeTexture = schwärmeTexture;
	mAngreiferShotTexture = angreiferShotTexture;
	mEnemyExplosion = enemyExplosion; //TODO:: Make them explode

	mNumberOfMinenlegers = 3;
	mNumberOfUnters = 3;

	SpawnMinenlegers();
	SpawnUnters();

	EnemyCitySpawner::Initialize(angreiferTexture, angreiferShotTexture, stadt_AngreiferTexture, angreiferTextureFC, bombTexture, bombExplosion, enemyExplosion, windowSize, worldBounds);
}

void EnemySpawner::PlayerPointer(std::shared_ptr<Player> playerSP)
{
	pPlayer = playerSP;
	EnemyCitySpawner::PlayerPointer(playerSP);
}

void EnemySpawner::CityPointer(std::shared_ptr<Cities> citySP)
{
	pCities = citySP;
	EnemyCitySpawner::CityPointer(citySP);
}

EnemySpawner::EnemySpawner(void)
{
	/* initialize random seed: */
	srand(unsigned(time(NULL)));	
}

void EnemySpawner::IsUnterHit(int ship)
{
	if (mUnters.at(ship)->GetActive())
	{
		if (mUnters.at(ship)->HitbyPlayerShot())
		{
			SpawnSchwärmes(*mUnters.at(ship)->GetPosition());			
		}
	}
}

void EnemySpawner::SpawnSchwärmes(sf::Vector2f position)
{
	for (int ship = 0; ship < 4; ship++)
	{
		bool spawnNewShip = true;
		int spawnShip = 0;

		for (size_t ship = 0; ship < mSchwärmes.size(); ship++)
		{
			if (!mSchwärmes.at(ship)->GetActive())
			{
				spawnNewShip = false;
				spawnShip = ship;
				break;
			}
		}

		if (spawnNewShip)
		{
			mSchwärmes.push_back(std::unique_ptr<Schwärme>(new Schwärme()));
			spawnShip = mSchwärmes.size() - 1;
			mSchwärmes.at(spawnShip)->Initialize(mSchwärmeTexture, mAngreiferShotTexture, mWindowSize, mWorldSize);
			mSchwärmes.at(spawnShip)->PlayerPointer(pPlayer);
		}

		mSchwärmes.at(spawnShip)->Setup((position), sf::Vector2f(float((rand() % 90) - 45), float((rand() % 40) - 20)));
	}
}

void EnemySpawner::SpawnUnters(void)
{
	for (int ship = 0; ship < mNumberOfUnters; ship++)
	{
		bool spawnNewShip = true;
		int spawnShip = 0;

		for (size_t ship = 0; ship < mUnters.size(); ship++)
		{
			if (!mUnters.at(ship)->GetActive())
			{
				spawnNewShip = false;
				spawnShip = ship;
				break;
			}
		}

		if (spawnNewShip)
		{
			mUnters.push_back(std::unique_ptr<Unter>(new Unter()));
			spawnShip = mUnters.size() - 1;
			mUnters.at(spawnShip)->Initialize(mUnterTexture, mWindowSize, mWorldSize);
			mUnters.at(spawnShip)->PlayerPointer(pPlayer);
		}

		float height = float((rand() % 10) + 20);
		float width = float(rand() % int(mWorldSize.x));
		mUnters.at(spawnShip)->Setup(sf::Vector2f(width, height), sf::Vector2f(float((rand() % 10) - 5), 1.0f));
	}
}

void EnemySpawner::SpawnMinenlegers(void)
{
	for (int ship = 0; ship < mNumberOfMinenlegers; ship++)
	{
		bool spawnNewShip = true;
		int spawnShip = 0;

		for (size_t ship = 0; ship < mMinenlegers.size(); ship++)
		{
			if (!mMinenlegers.at(ship)->GetActive())
			{
				spawnNewShip = false;
				spawnShip = ship;
				break;
			}
		}

		if (spawnNewShip)
		{
			mMinenlegers.push_back(std::unique_ptr<Minenleger>(new Minenleger()));
			spawnShip = mMinenlegers.size() - 1;
			mMinenlegers.at(spawnShip)->Initialize(mMinenlegerTexture, mMineTexture, mWindowSize, mWorldSize);
			mMinenlegers.at(spawnShip)->PlayerPointer(pPlayer);
		}

		float width = float(rand() % int(mWorldSize.x));
		float height;
		float yVelocity;
		float xVelocity;

		if (float(rand() %10) > 5)
			yVelocity = float((rand() % 10) +5);
		else
			yVelocity = float((rand() % 10) - 15);

		if (float(rand() % 10) > 5)
			xVelocity = float((rand() % 20) + 15);
		else
			xVelocity = float((rand() % 20) - 35);

		if (yVelocity > 0)
			height = 60;

		if (yVelocity < 0)
			height = float(mWindowSize.y - 100);

		mMinenlegers.at(spawnShip)->Setup(sf::Vector2f(width, height), sf::Vector2f(xVelocity, yVelocity));
	}
}
