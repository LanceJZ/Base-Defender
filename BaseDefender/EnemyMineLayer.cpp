#include "EnemyMineLayer.h"

void EnemyMineLayer::Update(sf::Time *delta, sf::Vector2f *position)
{
	for (size_t mine = 0; mine < mMines.size(); mine++)
	{
		mMines.at(mine)->Update(delta);
	}

	if (m_Active)
	{
		if (mNextMineTimer < mClock.getElapsedTime().asSeconds())
		{
			mNextMineTimer = MineTimer();
			LayMine(*position);
		}

		if (Entity::GetPosition()->x > m_WorldSize.x)
		{
			Entity::SetPosition(&sf::Vector2f(0, Entity::GetPosition()->y));
		}

		if (Entity::GetPosition()->x < 0.f)
		{
			Entity::SetPosition(&sf::Vector2f(m_WorldSize.x, Entity::GetPosition()->y));
		}
	}
}

void EnemyMineLayer::Draw(sf::RenderWindow *window)
{
	for (size_t mine = 0; mine < mMines.size(); mine++)
	{
		mMines.at(mine)->Draw(window);
	}
}

void EnemyMineLayer::DrawOtherSide(sf::RenderWindow *window)
{
	for (size_t mine = 0; mine < mMines.size(); mine++)
	{
		mMines.at(mine)->DrawOtherSide(window);
	}
}

void EnemyMineLayer::Initialize(sf::Texture *texture, sf::Vector2u windowSize, sf::Vector2f worldSize)
{
	mMineLaySpeed = 6.66f;
	mMineTexture = texture;
	mWindowSize = windowSize;
	mWorldSize = worldSize;

	mNextMineTimer = MineTimer();
}

void EnemyMineLayer::LayMine(sf::Vector2f position)
{
	bool spawnNewMine = true;
	int spawnMine = 0;

	for (size_t mineCheck = 0; mineCheck < mMines.size(); mineCheck++)
	{
		if (!mMines.at(mineCheck)->GetActive())
		{
			spawnNewMine = false;
			spawnMine = mineCheck;
			break;
		}
	}

	if (spawnNewMine)
	{
		spawnMine = SpawnNewMine();
	}

	SetupMine(position, spawnMine);
}

EnemyMineLayer::EnemyMineLayer(void)
{
}

float EnemyMineLayer::MineTimer(void)
{
	return mClock.getElapsedTime().asSeconds() + float(rand() % int(mMineLaySpeed)) + mMineLaySpeed / 2;
}

int EnemyMineLayer::SpawnNewMine(void)
{
	mMines.push_back(std::unique_ptr<EnemyMine>(new EnemyMine));
	mMines.at(mMines.size() - 1)->Initialize(mMineTexture, mWindowSize, mWorldSize);
	mMines.at(mMines.size() - 1)->PlayerPointer(pPlayer);

	return mMines.size() - 1;
}

void EnemyMineLayer::SetupMine(sf::Vector2f position, int mine)
{
	position.x += 15;
	position.y += 15;

	mMines.at(mine)->LayMine(position);
	mMines.at(mine)->SetActive(true);
}