#include "PlayerShot.h"

void PlayerShot::Update(sf::Time *Delta)
{
	Entity::Update(Delta);

	Entity::SetPosition(&sf::Vector2f(*Common::CheckForEdge(&Entity::GetPosition()->x, &Entity::m_WorldSize.x), Entity::GetPosition()->y));

	if (Entity::m_Active)
	{
		if (ShotOutOfTime())
			Entity::m_Active = false;
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
	Entity::m_Velocity = velocity;
	Entity::m_Active = true;
	mShotTimer = ShotTime();
}

sf::Vector2f *PlayerShot::GetPosition(void)
{
	return Entity::GetPosition();
}

bool PlayerShot::GetActive(void)
{
	return Entity::m_Active;
}

void PlayerShot::Hit(void)
{
	Entity::m_Active = false;
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