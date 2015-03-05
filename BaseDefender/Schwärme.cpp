#include "Schw�rme.h"

void Schw�rme::Update(sf::Time *delta)
{
	EnemyTargetedMover::Update(delta);	
	EnemyRandomShooter::Update(delta, EnemyTargetedMover::GetPosition());
	EnemyRandomShooter::SetActive(m_Active);

	if (EnemyTargetedMover::DoesMovementChange())
	{
		EnemyTargetedMover::ChaseTarget(Enemy::pPlayer->GetPosition());
	}
}

void Schw�rme::Draw(sf::RenderWindow *window)
{
	Enemy::Draw(window);
	EnemyRandomShooter::Draw(window);
}

void Schw�rme::DrawOtherSide(sf::RenderWindow *window)
{
	Enemy::DrawOtherSide(window);
	EnemyRandomShooter::DrawOtherSide(window);
}

void Schw�rme::Initialize(sf::Texture *texture, sf::Texture *shotTexture, sf::Texture *shipExplosion,
	sf::Vector2u windowSize, sf::Vector2f worldSize)
{
	EnemyTargetedMover::Initialize(texture, windowSize, worldSize);
	EnemyRandomShooter::Initialize(shotTexture, sf::Vector2i(texture->getSize().x / 2, texture->getSize().y / 2), windowSize, worldSize);
	Enemy::Initialize(shipExplosion);
}

void Schw�rme::Setup(sf::Vector2f position, sf::Vector2f velocity)
{
	Enemy::m_Active = true;
	EnemyTargetedMover::Setup(position, velocity);
	EnemyRandomShooter::SetActive(true);
}

void Schw�rme::PlayerPointer(std::shared_ptr<Player> playerSP)
{
	EnemyRandomShooter::PlayerPointer(playerSP);
	Enemy::pPlayer = playerSP;
}

void Schw�rme::SetActive(bool active)
{
	EnemyTargetedMover::SetActive(active);
	EnemyRandomShooter::SetActive(active);
}

bool Schw�rme::GetActive(void)
{
	return EnemyTargetedMover::GetActive();
}

Schw�rme::Schw�rme(void)
{
}
