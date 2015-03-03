#include "PlayerShot.h"

void PlayerShot::Update(sf::Time *Delta)
{
	Entity::Update(Delta);

	if (m_Active)
	{
		if (ShotOutOfTime())
			m_Active = false;
	}
}

void PlayerShot::Draw(sf::RenderWindow *window)
{
	Entity::Draw(window);
}

void PlayerShot::Initialize(sf::Texture *Texture, sf::Vector2u WindowSize, sf::Vector2f WorldBounds)
{
	Entity::Initialize(Texture, WindowSize, WorldBounds);
	mShotActiveTime = 0.93f;
}

void PlayerShot::Fire(sf::Vector2f position, sf::Vector2f velocity)
{
	Entity::SetPosition(&position);
	m_Velocity = velocity;
	m_Active = true;
	mShotTimer = ShotTime();
}

sf::Vector2f *PlayerShot::Position(void)
{
	return Entity::GetPosition();
}

bool PlayerShot::Active(void)
{
	return m_Active;
}

void PlayerShot::Hit(void)
{
	m_Active = false;
}

PlayerShot::PlayerShot()
{
}

float PlayerShot::ShotTime(void)
{
	return mClock.getElapsedTime().asSeconds() + mShotActiveTime;
}

bool PlayerShot::ShotOutOfTime(void)
{
	if (mShotTimer < mClock.getElapsedTime().asSeconds())
	{
		return true;
	}

	return false;
}