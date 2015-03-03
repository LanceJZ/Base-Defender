#include "EnemyShot.h"

void EnemyShot::Update(sf::Time *delta)
{
	Entity::Update(delta);

	if (m_Active)
	{
		ShotTimer();

		if (HitPlayer())
		{
			m_Active = false;
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
	pPlayer = playerSP;
}

void EnemyShot::FireShot(sf::Vector2f position)
{
	Entity::SetPosition(&position);
	m_Active = true;	
	mTimerLife = Common::ResetTimer(mTimerLife, mTimerLife * 1.5f, mTimerLife /2);
}

EnemyShot::EnemyShot(void)
{
}

void EnemyShot::ShotTimer(void)
{
	if (mTimerLife < mClock.getElapsedTime().asSeconds())
		m_Active = false;
}

bool EnemyShot::HitPlayer(void)
{
	if (GetCollision()->intersects(*pPlayer->GetCollision()))
		return true;

	return false;
}