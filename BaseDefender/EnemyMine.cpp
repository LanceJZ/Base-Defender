#include "EnemyMine.h"

void EnemyMine::Update(sf::Time *delta)
{
	Entity::Update(delta);

	if (m_Active)
	{
		MineTimer();
		HitbyPlayerShot();

		if (HitPlayer())
		{
			m_Active = false;
			pPlayer->PlayerHit();
		}
	}
}

void EnemyMine::Draw(sf::RenderWindow *window)
{
	if (m_Active)
	{
		Entity::Draw(window);
	}
}

void EnemyMine::DrawOtherSide(sf::RenderWindow *window)
{
	if (m_Active)
	{
		Entity::DrawOtherSide(window);
	}
}

void EnemyMine::Initialize(sf::Texture *texture, sf::Vector2u windowSize, sf::Vector2f worldSize)
{
	Entity::Initialize(texture, windowSize, worldSize);

	mTimerAmount = 30;
}

void EnemyMine::PlayerPointer(std::shared_ptr<Player> playerSP)
{
	pPlayer = playerSP;
}

void EnemyMine::LayMine(sf::Vector2f position)
{
	Entity::SetPosition(&position);
	m_Active = true;	
	mTimerLife = ResetTimer();
}

EnemyMine::EnemyMine(void)
{
}

bool EnemyMine::HitPlayer(void)
{
	if (GetCollision()->intersects(*pPlayer->GetCollision()))
		return true;

	return false;
}

float EnemyMine::ResetTimer(void)
{
	return mTimerAmount + mClock.getElapsedTime().asSeconds();
}

void EnemyMine::MineTimer(void)
{
	if (mTimerLife < mClock.getElapsedTime().asSeconds())
		m_Active = false;
}