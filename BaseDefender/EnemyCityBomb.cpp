#include "EnemyCityBomb.h"

void EnemyCityBomb::Update(sf::Time *delta)
{
	Enemy::Update(delta);

	if (Entity::m_Active)
	{
		if (mCityCollision->intersects(*Entity::GetCollision()))
		{
			HitTarget();
		}
	}

	sf::Vector2f pos = *GetPosition();
}

void EnemyCityBomb::Draw(sf::RenderWindow *window)
{
	Enemy::Draw(window);
}

void EnemyCityBomb::DrawOtherSide(sf::RenderWindow *window)
{
	Enemy::DrawOtherSide(window);
}

void EnemyCityBomb::Initialize(sf::Texture *texture, sf::Texture *explosionTexture, sf::Vector2u windowSize, sf::Vector2f worldSize)
{
	Entity::Initialize(texture, windowSize, worldSize);
	Enemy::Initialize(explosionTexture);
	mExplodeTimerAmount = 2.0f;
	mCityCollision = new sf::FloatRect;
}

void EnemyCityBomb::PlayerPointer(std::shared_ptr<Player> playerSP)
{
	Enemy::pPlayer = playerSP;
}

void EnemyCityBomb::CityPointer(std::shared_ptr<Cities> citySP)
{
	pCities = citySP;
}

void EnemyCityBomb::CityInfo(sf::Vector2f cityPosition, float cityWidth, int cityNumber)
{
	mCityCollision->top = cityPosition.y + 90;
	mCityCollision->left = cityPosition.x;
	mCityCollision->width = cityWidth;
	mCityCollision->height = 40;

	mCityBombing = cityNumber;
}

void EnemyCityBomb::DropBomb(sf::Vector2f position)
{
	Entity::SetPosition(&position);
	Entity::m_Active = true;
	Entity::m_Velocity.y = 0;
	Entity::m_Acceleration.y = 0.285f;
}

EnemyCityBomb::EnemyCityBomb(void)
{
}

void EnemyCityBomb::HitTarget(void)
{
	Entity::m_Active = false;
	Entity::m_Acceleration.y = 0;
	Entity::m_Velocity.y = 0;
	Enemy::Explode(*Entity::GetPosition(), mExplodeTimerAmount);
	pCities->BombHitCity(mCityBombing);
}
