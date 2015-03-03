#include "Angreifer.h"

void Angreifer::Update(sf::Time *delta)
{
	EnemyRandomShooter::SetActiveShot(m_Active);
	EnemyRandomShooter::Update(delta, Entity::GetPosition());
	EnemyRandomMover::Update(delta);
}

void Angreifer::Draw(sf::RenderWindow *window)
{
	Entity::Draw(window);
	EnemyRandomShooter::Draw(window);
}

void Angreifer::DrawOtherSide(sf::RenderWindow *window)
{
	Entity::DrawOtherSide(window);
	EnemyRandomShooter::DrawOtherSide(window);
}

void Angreifer::Initialize(sf::Texture *texture, sf::Texture *shotTexture, sf::Vector2u windowSize, sf::Vector2f worldSize)
{
	EnemyRandomShooter::Initialize(shotTexture, sf::Vector2i(texture->getSize().x / 2, texture->getSize().y / 2), windowSize, worldSize);
	EnemyRandomMover::Initialize(texture, windowSize, worldSize);
}

void Angreifer::Setup(sf::Vector2f position, sf::Vector2f velocity)
{
	EnemyRandomShooter::SetActiveShot(true);
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
	EnemyRandomShooter::SetActiveShot(active);
}

bool Angreifer::GetActive(void)
{
	return EnemyRandomMover::GetActive();
}

Angreifer::Angreifer(void)
{	
}
