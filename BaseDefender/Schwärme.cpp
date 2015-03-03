#include "Schwärme.h"

void Schwärme::Update(sf::Time *delta)
{
	EnemyTargetedMover::Update(delta);	
	EnemyRandomShooter::Update(delta, EnemyTargetedMover::GetPosition());

	if (EnemyTargetedMover::DoesMovementChange())
	{
		EnemyTargetedMover::ChaseTarget(Enemy::pPlayer->GetPosition());
	}
}

void Schwärme::Draw(sf::RenderWindow *window)
{
	EnemyTargetedMover::Draw(window);
	EnemyRandomShooter::Draw(window);
}

void Schwärme::DrawOtherSide(sf::RenderWindow *window)
{
	EnemyTargetedMover::DrawOtherSide(window);
	EnemyRandomShooter::DrawOtherSide(window);
}

void Schwärme::Initialize(sf::Texture *texture, sf::Texture *shotTexture, sf::Vector2u windowSize, sf::Vector2f worldSize)
{
	EnemyTargetedMover::Initialize(texture, windowSize, worldSize);
	EnemyRandomShooter::Initialize(shotTexture, sf::Vector2i(texture->getSize().x / 2, texture->getSize().y / 2), windowSize, worldSize);
}

void Schwärme::Setup(sf::Vector2f position, sf::Vector2f velocity)
{
	Enemy::m_Active = true;
	EnemyTargetedMover::Setup(position, velocity);
	EnemyRandomShooter::SetActiveShot(true);
}

void Schwärme::PlayerPointer(std::shared_ptr<Player> playerSP)
{
	EnemyRandomShooter::PlayerPointer(playerSP);
	Enemy::pPlayer = playerSP;
}

void Schwärme::SetActive(bool active)
{
	EnemyTargetedMover::SetActive(active);
	EnemyRandomShooter::SetActiveShot(active);
}

bool Schwärme::GetActive(void)
{
	return EnemyTargetedMover::GetActive();
}

Schwärme::Schwärme(void)
{
}
