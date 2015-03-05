#include "EnemyShot.h"

void EnemyShot::Update(sf::Time *delta)
{
	Entity::Update(delta);

	if (Entity::m_Active)
	{
		ShotTimer();

		if (Enemy::HitPlayer())
		{
			Entity::m_Active = false;
			pPlayer->PlayerHit();
		}
	}
}

void EnemyShot::Draw(sf::RenderWindow *window)
{
	Entity::Draw(window);
}

void EnemyShot::DrawOtherSide(sf::RenderWindow *window)
{
	Entity::DrawOtherSide(window);
}

void EnemyShot::Initialize(sf::Texture *texture, sf::Vector2u windowSize, sf::Vector2f worldSize)
{
	Entity::Initialize(texture, windowSize, worldSize);

	mTimerAmount = 5;
}

void EnemyShot::PlayerPointer(std::shared_ptr<Player> playerSP)
{
	Enemy::pPlayer = playerSP;
}

void EnemyShot::FireShot(sf::Vector2f position)
{
	Entity::SetPosition(&position);
	Entity::m_Active = true;
	mTimerLife = Common::ResetTimer(mTimerAmount, mTimerAmount / 2);
}

EnemyShot::EnemyShot(void)
{
}

void EnemyShot::ShotTimer(void)
{
	if (mTimerLife < mClock.getElapsedTime().asSeconds())
		Entity::m_Active = false;
}
