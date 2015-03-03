#include "EnemyCityBomb.h"

void EnemyCityBomb::Update(sf::Time *delta)
{
	Entity::Update(delta);

	if (Entity::m_Active)
	{
		if (mCityCollision->intersects(*Entity::GetCollision()))
		{
			HitTarget();
		}
	}
	else if (mExploding)
	{
		if (mExplodeTimer < mClock.getElapsedTime().asSeconds())
			mExploding = false;
	}

	sf::Vector2f pos = *GetPosition();
}

void EnemyCityBomb::Draw(sf::RenderWindow *window)
{
	Entity::Draw(window);

	if (mExploding)
		window->draw(*mBombExplosion);
}

void EnemyCityBomb::DrawOtherSide(sf::RenderWindow *window)
{
	Entity::DrawOtherSide(window);

	if (mExploding)
	{
		if (mBombExplosion->getPosition().x < 1.0f || mBombExplosion->getPosition().x > m_WorldSize.x - Entity::GetCollision()->width)
		{
			mBombExplosion->setPosition(mBombExplosion->getPosition().x - m_WorldSize.x, mBombExplosion->getPosition().y);
			window->draw(*mBombExplosion);
		}
	}
}

void EnemyCityBomb::Initialize(sf::Texture *texture, sf::Texture *bombExplosion, sf::Vector2u windowSize, sf::Vector2f worldSize)
{
	Entity::Initialize(texture, windowSize, worldSize);
	mExplodeTimerAmount = 1.5f;
	mExplodeTimer;
	mCityCollision = new sf::FloatRect;
	mBombExplosion = new sf::Sprite;
	mBombExplosion->setTexture(*bombExplosion);
}

void EnemyCityBomb::PlayerPointer(std::shared_ptr<Player> playerSP)
{
	pPlayer = playerSP;
}

void EnemyCityBomb::CityInfo(sf::Vector2f cityPosition, float cityWidth)
{
	mCityCollision->top = cityPosition.y + 90;
	mCityCollision->left = cityPosition.x;
	mCityCollision->width = cityWidth;
	mCityCollision->height = 40;
}

void EnemyCityBomb::DropBomb(sf::Vector2f position)
{
	Entity::SetPosition(&position);
	Entity::m_Active = true;
	Entity::m_Velocity.y = 0;
	Entity::m_Acceleration.y = 0.285f;
	mExploding = false;	
}

EnemyCityBomb::EnemyCityBomb(void)
{
}

void EnemyCityBomb::HitTarget(void)
{
	Entity::m_Active = false;
	Entity::m_Acceleration.y = 0;
	Entity::m_Velocity.y = 0;
	sf::Vector2f bombPosition = *Entity::GetPosition();
	bombPosition.y = bombPosition.y - mBombExplosion->getTextureRect().height / 2;
	bombPosition.x = bombPosition.x - mBombExplosion->getTextureRect().width / 2;
	mExploding = true;
	mExplodeTimer = ResetTimer(mExplodeTimerAmount, mExplodeTimerAmount / 1.25f, mExplodeTimerAmount / 4);
	mBombExplosion->setPosition(bombPosition);
}
