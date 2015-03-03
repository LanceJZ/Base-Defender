#include "EnemyRandomShooter.h"

void EnemyRandomShooter::Update(sf::Time *delta, sf::Vector2f *position)
{
	for (size_t shot = 0; shot < mShots.size(); shot++)
	{
		mShots.at(shot)->Update(delta);
	}

	if (mActive)
	{
		if (mNextShotTime < mClock.getElapsedTime().asSeconds())
		{
			mNextShotTime = ShotTime();
			FireShot(*position);
		}
	}
}

void EnemyRandomShooter::Draw(sf::RenderWindow *window)
{
	for (size_t shot = 0; shot < mShots.size(); shot++)
	{
		mShots.at(shot)->Draw(window);
	}
}

void EnemyRandomShooter::DrawOtherSide(sf::RenderWindow *window)
{
	for (size_t shot = 0; shot < mShots.size(); shot++)
	{
		mShots.at(shot)->DrawOtherSide(window);
	}
}

void EnemyRandomShooter::FireShot(sf::Vector2f position) //Shot Factory, Offset amount of X and Y to move position to offset shot origin.
{
	bool spawnNewShot = true;
	int spawnShot = 0;

	for (size_t shotCheck = 0; shotCheck < mShots.size(); shotCheck++)
	{
		if (!mShots.at(shotCheck)->GetActive())
		{
			spawnNewShot = false;
			spawnShot = shotCheck;
			break;
		}
	}

	if (spawnNewShot)
	{
		spawnShot = SpawnNewShot();
	}

	SetupShot(sf::Vector2f(position.x + mOffset.x, position.y + mOffset.y), spawnShot);
}

int EnemyRandomShooter::SpawnNewShot(void)
{
	mShots.push_back(std::unique_ptr<EnemyShot>(new EnemyShot));
	mShots.at(mShots.size() - 1)->Initialize(mShotTexture, mWindowSize, mWorldSize);
	mShots.at(mShots.size() - 1)->PlayerPointer(pPlayer);

	return mShots.size() - 1;
}

void EnemyRandomShooter::SetupShot(sf::Vector2f position, int shot)
{	
	mShots.at(shot)->FireShot(position);
	mShots.at(shot)->SetActive(true);
	mShots.at(shot)->SetVelocity(&RandomShotVector());
}

void EnemyRandomShooter::Initialize(sf::Texture *Texture, sf::Vector2i offset, sf::Vector2u WindowSize, sf::Vector2f WorldBounds)
{
	mShotSpeed = 2.5f;
	mShotTimer = 12.5f;

	mShotTexture = Texture;
	mWindowSize = WindowSize;
	mWorldSize = WorldBounds;
	mOffset = offset;

	mNextShotTime = ShotTime();
}

void EnemyRandomShooter::PlayerPointer(std::shared_ptr<Player> playerSP)
{
	pPlayer = playerSP;
}

bool EnemyRandomShooter::GetActiveShot(void)
{
	return mActive;
}

void EnemyRandomShooter::SetActiveShot(bool active)
{
	mActive = active;
}

EnemyRandomShooter::EnemyRandomShooter(void)
{	
}

float EnemyRandomShooter::ShotTime(void)
{
	return mClock.getElapsedTime().asSeconds() + float(rand() % int(mShotTimer)) + mShotTimer / 2;
}

sf::Vector2f EnemyRandomShooter::RandomShotVector(void)
{
	float random = rand() / (RAND_MAX + 1.0f);
	float angle = random * 2.0f * (float)M_PI;

	return Common::AngleToVector(angle, 100);
}