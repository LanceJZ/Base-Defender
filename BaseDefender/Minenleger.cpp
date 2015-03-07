#include "Minenleger.h"

void Minenleger::Update(sf::Time *delta)
{
	EnemyMineLayer::Update(delta);

	if (m_Active)
	{
		CheckEdge();
	}
}

void Minenleger::Draw(sf::RenderWindow *window)
{
	EnemyMineLayer::Draw(window);
}

void Minenleger::DrawOtherSide(sf::RenderWindow *window)
{
	EnemyMineLayer::DrawOtherSide(window);
}

void Minenleger::Initialize(sf::Texture *texture, sf::Texture *radarTexture, sf::Texture *bombTexture, sf::Texture *shipExplosion,
	sf::Vector2u windowSize, sf::Vector2f worldSize)
{
	Entity::Initialize(texture, windowSize, worldSize);
	EnemyMineLayer::Initialize(bombTexture, windowSize, worldSize);
	Enemy::Initialize(shipExplosion);
	Enemy::mRadar->setTexture(*radarTexture);
}

void Minenleger::Setup(sf::Vector2f position, sf::Vector2f velocity)
{
	m_Active = true;
	m_Velocity = velocity;
	Entity::SetPosition(&position);
}

void Minenleger::PlayerPointer(std::shared_ptr<Player> playerSP)
{
	pPlayer = playerSP;
}

Minenleger::Minenleger(void)
{
}

void Minenleger::CheckEdge(void)
{
	sf::Vector2f position(*Entity::GetPosition());
	sf::Vector2f atPosition(*Entity::GetPosition());

	if (atPosition.y > m_WindowSize.y - 100)
		position.y = 60 + float(Entity::GetCollision()->height / 2);

	if (atPosition.y < 60)
		position.y = float(m_WindowSize.y - 100 - Entity::GetCollision()->height / 2);

	Entity::SetPosition(&position);
}