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

void EnemySpawner::DrawRadar(sf::RenderWindow *window)
{
	for (size_t ship = 0; ship < mMinenlegers.size(); ship++)
	{
		mMinenlegers.at(ship)->DrawRadar(window);
	}

	for (size_t ship = 0; ship < mUnters.size(); ship++)
	{
		mUnters.at(ship)->DrawRadar(window);
	}

	for (size_t ship = 0; ship < mSchwärmes.size(); ship++)
	{
		mSchwärmes.at(ship)->DrawRadar(window);
	}

	EnemyCitySpawner::DrawRadar(window);
}

void EnemySpawner::Initialize(sf::Texture *minenlegerTexture, sf::Texture *mineTexture, sf::Texture *unterTexture, sf::Texture *schwärmeTexture, sf::Texture *shotTexture, sf::Texture *enemyExplosion,
	sf::Vector2u windowSize, sf::Vector2f worldBounds)
{
	mWindowSize = windowSize;
	mWorldSize = worldBounds;
	mMinenlegerTexture = minenlegerTexture;
	mMineTexture = mineTexture;
	mUnterTexture = unterTexture;
	mSchwärmeTexture = schwärmeTexture;
	mShotTexture = shotTexture;
	mEnemyExplosion = enemyExplosion;

	mNumberOfMinenlegers = 3;
	mNumberOfUnters = 3;

	SpawnMinenlegers();
	SpawnUnters();	
}

void EnemySpawner::InitializeCityEnemys(sf::Texture *angreiferTexture, sf::Texture *stadt_AngreiferTexture,
	sf::Texture *angreiferTextureFC, sf::Texture *jägerTexture, sf::Texture *bombTexture, sf::Texture *bombExplosion)
{
	EnemyCitySpawner::Initialize(angreiferTexture, mShotTexture, stadt_AngreiferTexture, angreiferTextureFC, jägerTexture, bombTexture, bombExplosion, mEnemyExplosion, mWindowSize, mWorldSize);
}

void EnemySpawner::InitializeRadar(sf::Texture *minenlegerRadarTexture, sf::Texture *unterRadarTexture, sf::Texture *schwärmeRadarTexture)
{	
	mMinenlegerRadarTexture = minenlegerRadarTexture;
	mUnterRadarTexture = unterRadarTexture;
	mSchwärmeRadarTexture = schwärmeRadarTexture;
}

void EnemySpawner::InitializeCityEnemyRadar(sf::Texture *angreiferRadarTexture, sf::Texture *jägerRadarTexture)
{
	EnemyCitySpawner::InitializeRadar(angreiferRadarTexture, jägerRadarTexture);
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
}

void EnemySpawner::IsUnterHit(int ship)
{
	if (mUnters.at(ship)->GetActive())
	{
		if (mUnters.at(ship)->HitbyPlayerShot())
		{
			SpawnSchwärmes(*mUnters.at(ship)->GetPosition());
			mUnters.at(ship)->Explode(*mUnters.at(ship)->GetPosition(), 2.5f);
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
			mSchwärmes.at(spawnShip)->Initialize(mSchwärmeTexture, mSchwärmeRadarTexture, mShotTexture, mEnemyExplosion, mWindowSize, mWorldSize);
			mSchwärmes.at(spawnShip)->PlayerPointer(pPlayer);
		}

		mSchwärmes.at(spawnShip)->Setup((position), sf::Vector2f(Common::RandomNumber(-45.0f, 45.0f), Common::RandomNumber(-20.0f, 20.0f)));
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
			mUnters.at(spawnShip)->Initialize(mUnterTexture, mUnterRadarTexture, mEnemyExplosion, mWindowSize, mWorldSize);
			mUnters.at(spawnShip)->PlayerPointer(pPlayer);
		}

		mUnters.at(spawnShip)->Setup(sf::Vector2f(Common::RandomNumber(10.0f, mWorldSize.x), Common::RandomNumber(20, 30)), sf::Vector2f(Common::RandomNumber(-5.0f, 10.0f), 1.0f));
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
			mMinenlegers.at(spawnShip)->Initialize(mMinenlegerTexture, mMinenlegerRadarTexture, mMineTexture, mEnemyExplosion, mWindowSize, mWorldSize);
			mMinenlegers.at(spawnShip)->PlayerPointer(pPlayer);
		}

		float height;
		float xVelocity;
		float yVelocity;

		if (Common::RandomNumber(0.0f, 10.0f) > 5.0f)
			xVelocity = Common::RandomNumber(15.0f, 35.0f);
		else
			xVelocity = Common::RandomNumber(-15.0f, -35.0f);

		if (Common::RandomNumber(0.0f, 10.0f) > 5.0f)
			yVelocity = Common::RandomNumber(-5.0f, -15.0f);
		else
			yVelocity = Common::RandomNumber(5.0f, 15.0f);

		if (yVelocity > 0)
			height = 60.0f;
		else
			height = float(mWindowSize.y - 100);

		mMinenlegers.at(spawnShip)->Setup(sf::Vector2f(Common::RandomNumber(10.0f, mWorldSize.x), height), sf::Vector2f(xVelocity, yVelocity));
	}
}
