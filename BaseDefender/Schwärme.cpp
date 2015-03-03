#include "Schw�rme.h"

void Schw�rme::Update(sf::Time *delta)
{
	EnemyTargetedMover::Update(delta);	
	EnemyRandomShooter::Update(delta, EnemyTargetedMover::GetPosition());

	if (EnemyTargetedMover::DoesMovementChange())
	{
		EnemyTargetedMover::ChaseTarget(Enemy::pPlayer->GetPosition());
	}
}

void Schw�rme::Draw(sf::RenderWindow *window)
{
	EnemyTargetedMover::Draw(window);
	EnemyRandomShooter::Draw(window);
}

void Schw�rme::DrawOtherSide(sf::RenderWindow *window)
{
	EnemyTargetedMover::DrawOtherSide(window);
	EnemyRandomShooter::DrawOtherSide(window);
}

void Schw�rme::Initialize(sf::Texture *texture, sf::Texture *shotTexture, sf::Vector2u windowSize, sf::Vector2f worldSize)
{
	EnemyTargetedMover::Initialize(texture, windowSize, worldSize);
	EnemyRandomShooter::Initialize(shotTexture, sf::Vector2i(texture->getSize().x / 2, texture->getSize().y / 2), windowSize, worldSize);
}

void Schw�rme::Setup(sf::Vector2f position, sf::Vector2f velocity)
{
	Enemy::m_Active = true;
	EnemyTargetedMover::Setup(position, velocity);
	EnemyRandomShooter::SetActiveShot(true);
}

void Schw�rme::PlayerPointer(std::shared_ptr<Player> playerSP)
{
	EnemyRandomShooter::PlayerPointer(playerSP);
	Enemy::pPlayer = playerSP;
}

void Schw�rme::SetActive(bool active)
{
	EnemyTargetedMover::SetActive(active);
	EnemyRandomShooter::SetActiveShot(active);
}

bool Schw�rme::GetActive(void)
{
	return EnemyTargetedMover::GetActive();
}

Schw�rme::Schw�rme(void)
{
}
