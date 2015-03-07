#include "Enemy.h"

void Enemy::Update(sf::Time *delta)
{
	Entity::Update(delta);
	Entity::SetPosition(&sf::Vector2f(*Common::CheckForEdge(&Entity::GetPosition()->x, &Entity::m_WorldSize.x), Entity::GetPosition()->y));

	if (mExploding)
	{
		if (mTimerExplode < mClock.getElapsedTime().asSeconds())
			mExploding = false;
	}

	if (Entity::m_Active)
	{
		if (pPlayer != NULL)
		{
			if (HitbyPlayerShot())
				Explode(*Entity::GetPosition(), 2.0f);

			if (HitPlayer())
				Explode(*Entity::GetPosition(), 2.0f);
		
			if (mRadar->getTexture() != NULL)
				UpdateRadar();
		}
	}
}

void Enemy::UpdateRadar(void)
{
	float playerX = (pPlayer->GetPosition()->x + pPlayer->GetCollision()->width * 0.5f);
	float radarX = (Entity::GetPosition()->x - playerX) *0.1f;
	
	playerX *= 0.1f;
	radarX += float(m_WindowSize.x * 2) * 0.1f;
	radarX += float(int(m_WindowSize.x * 0.5f) - 256);

	if (radarX > 895)
		radarX -= 512;

	if (radarX < 383)
		radarX += 512;

	mRadar->setPosition(sf::Vector2f(radarX, Entity::GetPosition()->y * 0.1f + m_WorldSize.y + 55));
}

void Enemy::Draw(sf::RenderWindow *window)
{
	Entity::Draw(window);

	if (mExploding)
		window->draw(*mExplosion);
}

void Enemy::DrawOtherSide(sf::RenderWindow *window)
{
	Entity::DrawOtherSide(window);

	if (mExploding)
	{
		if (mExplosion->getPosition().x < 1.0f || mExplosion->getPosition().x > m_WorldSize.x - Entity::GetCollision()->width)
		{
			mExplosion->setPosition(mExplosion->getPosition().x - m_WorldSize.x, mExplosion->getPosition().y);
			window->draw(*mExplosion);
		}
	}
}

void Enemy::DrawRadar(sf::RenderWindow *window)
{
	if (Entity::m_Active)
		window->draw(*mRadar);
}

void Enemy::Initialize(sf::Texture *explosionTexture)
{
	mExplosion->setTexture(*explosionTexture);
}

bool Enemy::HitbyPlayerShot(void)
{
	for (size_t shot = 0; shot < pPlayer->ShotCount(); shot++)
	{
		if (pPlayer->ShotActive(shot))
		{
			if (Entity::GetCollision()->intersects(*pPlayer->ShotCollision(shot)))
			{
				pPlayer->ShotHit(shot);
				Entity::m_Active = false;
				return true;
			}
		}
	}

	return false;
}

bool Enemy::HitPlayer(void)
{
	if (Entity::GetCollision()->intersects(*pPlayer->GetCollision()))
		return true;

	return false;
}

Enemy::Enemy()
{
	mMaxVolicityX = 33.666f;
	mMaxVolicityY = 6.666f;
	mExploding = false;
	mExplosion = new sf::Sprite();
	mRadar = new sf::Sprite();
}

void Enemy::CheckVelocity(void)
{
	if (Entity::GetPosition()->y > m_WindowSize.y - 160 || Entity::GetPosition()->y < 60)
	{
		m_Velocity.y = 0;

		if (Entity::GetPosition()->y < 60)
			Entity::m_Acceleration.y = 5;

		if (Entity::GetPosition()->y > Entity::m_WindowSize.y - 160)
			Entity::m_Acceleration.y = -5;
	}

	if (GetVelocity()->x > mMaxVolicityX)
	{
		SetAcceleration(&sf::Vector2f(0.0f, Entity::m_Acceleration.y));
		SetVelocity(&sf::Vector2f(mMaxVolicityX, Entity::m_Velocity.y));
	}

	if (GetVelocity()->x < -mMaxVolicityX)
	{
		SetAcceleration(&sf::Vector2f(0.0f, Entity::m_Acceleration.y));
		SetVelocity(&sf::Vector2f(-mMaxVolicityX, Entity::m_Velocity.y));
	}

	if (GetVelocity()->y > mMaxVolicityY)
	{
		SetAcceleration(&sf::Vector2f(Entity::m_Acceleration.x, 0.0f));
		SetVelocity(&sf::Vector2f(Entity::m_Velocity.x, mMaxVolicityY));
	}

	if (GetVelocity()->y < -mMaxVolicityY)
	{
		SetAcceleration(&sf::Vector2f(Entity::m_Acceleration.x, 0.0f));
		SetVelocity(&sf::Vector2f(Entity::m_Velocity.x, -mMaxVolicityY));
	}
}

void Enemy::Explode(sf::Vector2f position, float duration)
{
	if (mExplosion != NULL)
	{
		//Puts center of explosion over position.
		position.x = position.x - mExplosion->getTextureRect().width / 2 + Entity::GetCollision()->width / 2;
		position.y = position.y - mExplosion->getTextureRect().height / 2 + Entity::GetCollision()->height / 2;
		mExplosion->setPosition(position);
		mExploding = true;
		float test = mClock.getElapsedTime().asSeconds();
		mTimerExplode = Common::ResetTimer(duration, duration / 4);
		float tester = mClock.getElapsedTime().asSeconds();
	}
}