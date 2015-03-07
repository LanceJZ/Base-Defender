#include "Unter.h"

void Unter::Update(sf::Time *delta)
{
	EnemyRandomMover::Update(delta);
}

void Unter::Draw(sf::RenderWindow *window)
{
	Enemy::Draw(window);
}

void Unter::DrawOtherSide(sf::RenderWindow *window)
{
	Enemy::DrawOtherSide(window);
}

void Unter::Initialize(sf::Texture *texture, sf::Texture *radarTexture, sf::Texture *shipExplosion, sf::Vector2u windowSize, sf::Vector2f worldSize)
{
	EnemyRandomMover::Initialize(texture, windowSize, worldSize);
	Enemy::Initialize(shipExplosion);

	if (radarTexture != NULL)
		Enemy::mRadar->setTexture(*radarTexture);
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
