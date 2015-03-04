#include "City.h"

void City::Initialize(sf::Texture *texture, sf::Vector2u windowSize, sf::Vector2f worldSize, sf::Vector2f position)
{
	Entity::Initialize(texture, windowSize, worldSize);
	Entity::SetPosition(&position);
	Entity::UpdateCollusionPosition();
	m_Active = true;
}

void City::Update(sf::Time *delta)
{
	//Entity::Update(delta);
}

void City::Draw(sf::RenderWindow *window)
{
	Entity::Draw(window);
}

City::City(void)
{
}
