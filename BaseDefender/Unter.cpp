#include "Unter.h"

void Unter::Update(sf::Time *delta)
{
	EnemyRandomMover::Update(delta);
}

void Unter::Draw(sf::RenderWindow *window)
{
	Entity::Draw(window);
}

void Unter::DrawOtherSide(sf::RenderWindow *window)
{
	Entity::DrawOtherSide(window);
}

void Unter::Initialize(sf::Texture *texture, sf::Vector2u windowSize, sf::Vector2f worldSize)
{
	EnemyRandomMover::Initialize(texture, windowSize, worldSize);
}

void Unter::PlayerPointer(std::shared_ptr<Player> playerSP)
{
	Enemy::pPlayer = playerSP;
}

bool Unter::HitbyPlayerShot(void)
{
	return Enemy::HitbyPlayerShot();
}

Unter::Unter(void)
{
}
