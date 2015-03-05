#include "EnemyMine.h"

void EnemyMine::Update(sf::Time *delta)
{
	Entity::Update(delta);

	if (Entity::m_Active)
	{
		MineTimer();
		Enemy::HitbyPlayerShot();

		if (Enemy::HitPlayer())
		{
			Entity::m_Active = false;
			Enemy::pPlayer->PlayerHit();
		}
	}
}

void EnemyMine::Draw(sf::RenderWindow *window)
{
		Entity::Draw(window);
}

void EnemyMine::DrawOtherSide(sf::RenderWindow *window)
{
		Entity::DrawOtherSide(window);
}

void EnemyMine::Initialize(sf::Texture *texture, sf::Vector2u windowSize, sf::Vector2f worldSize)
{
	Entity::Initialize(texture, windowSize, worldSize);

	mTimerAmount = 30;
}

void EnemyMine::PlayerPointer(std::shared_ptr<Player> playerSP)
{
	Enemy::pPlayer = playerSP;
}

void EnemyMine::LayMine(sf::Vector2f position)
{
	Entity::SetPosition(&position);
	Entity::m_Active = true;
	mTimerLife = Common::ResetTimer(mTimerAmount, mTimerAmount / 4);
}

EnemyMine::EnemyMine(void)
{
}

void EnemyMine::MineTimer(void)
{
	if (mTimerLife < mClock.getElapsedTime().asSeconds())
		Entity::m_Active = false;
}