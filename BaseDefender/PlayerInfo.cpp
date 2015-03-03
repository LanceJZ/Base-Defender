#include "PlayerInfo.h"

void PlayerInfo::SetActive(bool Active)
{
	mActive = Active;
}

void PlayerInfo::SetPosition(sf::Vector2f Position)
{
	mPosition = Position;
}

void PlayerInfo::SetCollision(sf::FloatRect Collision)
{
	mCollision = Collision;
}

bool PlayerInfo::GetActive(void)
{
	return mActive;
}

sf::Vector2f PlayerInfo::GetPosision(void)
{
	return mPosition;
}

sf::FloatRect PlayerInfo::GetCollision(void)
{
	return mCollision;
}

PlayerInfo::PlayerInfo()
{
}