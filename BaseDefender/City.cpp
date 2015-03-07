#include "City.h"

void City::Initialize(sf::Texture *texture, sf::Texture *radarTexture, sf::Vector2u windowSize, sf::Vector2f worldSize, sf::Vector2f position)
{
	Entity::Initialize(texture, windowSize, worldSize);
	Entity::SetPosition(&position);
	Entity::UpdateCollusionPosition();
	mRadar->setTexture(*radarTexture);
	m_Active = true;
}

void City::Update(sf::Time *delta, float *playerX)
{
	float pX = *playerX;
	pX += 64;
	float radarX = (Entity::GetPosition()->x - pX) *0.1f;

	pX *= 0.1f;
	radarX += float(m_WindowSize.x * 2) * 0.1f;
	radarX += float(int(m_WindowSize.x * 0.5f) - 256);

	if (radarX > 895)
		radarX -= 512;

	if (radarX < 383)
		radarX += 512;

	mRadar->setPosition(sf::Vector2f(radarX, float(int(m_WindowSize.y) - mRadar->getTextureRect().height)));
}

void City::Draw(sf::RenderWindow *window)
{
	Entity::Draw(window);
}

void City::DrawRadar(sf::RenderWindow *window)
{
	window->draw(*mRadar);
}

City::City(void)
{
	mRadar = new sf::Sprite();
}
