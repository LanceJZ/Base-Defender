#include "Enemy.h"

bool Enemy::HitbyPlayerShot(void)
{
	for (size_t shot = 0; shot < pPlayer->ShotCount(); shot++)
	{
		if (pPlayer->ShotActive(shot))
		{
			if (Entity::GetCollision()->intersects(pPlayer->ShotCollision(shot)))
			{
				pPlayer->ShotHit(shot);
				m_Active = false;
				return true;
			}
		}
	}

	return false;
}

Enemy::Enemy()
{
	mMaxVolicityX = 33.666f;
	mMaxVolicityY = 6.666f;
}

void Enemy::CheckVelocity(void)
{
	sf::Vector2f position = *Entity::GetPosition();

	if (position.y > m_WindowSize.y - 160 || position.y < 60)
	{
		m_Velocity.y = 0;

		if (position.y < 60)
			m_Acceleration.y = 5;

		if (position.y > m_WindowSize.y - 160)
			m_Acceleration.y = -5;
	}

	if (GetVelocity()->x > mMaxVolicityX)
	{
		SetAcceleration(&sf::Vector2f(0.0f, m_Acceleration.y));
		SetVelocity(&sf::Vector2f(mMaxVolicityX, m_Velocity.y));
	}

	if (GetVelocity()->x < -mMaxVolicityX)
	{
		SetAcceleration(&sf::Vector2f(0.0f, m_Acceleration.y));
		SetVelocity(&sf::Vector2f(-mMaxVolicityX, m_Velocity.y));
	}

	if (GetVelocity()->y > mMaxVolicityY)
	{
		SetAcceleration(&sf::Vector2f(m_Acceleration.x, 0.0f));
		SetVelocity(&sf::Vector2f(m_Velocity.x, mMaxVolicityY));
	}

	if (GetVelocity()->y < -mMaxVolicityY)
	{
		SetAcceleration(&sf::Vector2f(m_Acceleration.x, 0.0f));
		SetVelocity(&sf::Vector2f(m_Velocity.x, -mMaxVolicityY));
	}
}