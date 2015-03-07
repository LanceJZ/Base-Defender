#include "Angreifer.h"

void Angreifer::Update(sf::Time *delta)
{
	EnemyRandomShooter::SetActive(m_Active);
	EnemyRandomShooter::Update(delta, Entity::GetPosition());
	EnemyRandomMover::Update(delta);
}

void Angreifer::Draw(sf::RenderWindow *window)
{
	Enemy::Draw(window);
	EnemyRandomShooter::Draw(window);
}

void Angreifer::DrawOtherSide(sf::RenderWindow *window)
{
	Enemy::DrawOtherSide(window);
	EnemyRandomShooter::DrawOtherSide(window);
}

void Angreifer::Initialize(sf::Texture *texture, sf::Texture *radarTexture, sf::Texture *shotTexture, sf::Texture *shipExplosion,
	sf::Vector2u windowSize, sf::Vector2f worldSize)
{
	EnemyRandomShooter::Initialize(shotTexture, sf::Vector2i(texture->getSize().x / 2, texture->getSize().y / 2), windowSize, worldSize);
	EnemyRandomMover::Initialize(texture, windowSize, worldSize);
	Enemy::Initialize(shipExplosion);
	Enemy::mRadar->setTexture(*radarTexture);
}

void Angreifer::Setup(sf::Vector2f position, sf::Vector2f velocity)
{
	EnemyRandomShooter::SetActive(true);
	EnemyRandomMover::Setup(position, velocity);
}

void Angreifer::PlayerPointer(std::shared_ptr<Player> playerSP)
{
	EnemyRandomShooter::PlayerPointer(playerSP); //This is so a shot will know when it hits the player.
	Enemy::pPlayer = playerSP;
}

void Angreifer::SetActive(bool active)
{
	EnemyRandomMover::SetActive(active);
	EnemyRandomShooter::SetActive(active);
}

bool Angreifer::GetActive(void)
{
	return EnemyRandomMover::GetActive();
}

Angreifer::Angreifer(void)
{	
}
