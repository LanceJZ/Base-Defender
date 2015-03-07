#include "Cities.h"

void Cities::Update(sf::Time *delta, float *playerX)
{
	for (int city = 0; city < 4; city++)
	{
		mCities[city].Update(delta, playerX);
	}
}

void Cities::Draw(sf::RenderWindow *window)
{
	for (int city = 0; city < 4; city++)
	{
		mCities[city].Draw(window);
	}
}

void Cities::DrawRadar(sf::RenderWindow *window)
{
	for (int city = 0; city < 4; city++)
	{
		mCities[city].DrawRadar(window);
	}
}

void Cities::Initialize(sf::Texture *texture, sf::Texture *radarTexture, sf::Vector2u windowSize, sf::Vector2f worldSize)
{
	sf::Vector2f position;

	position.y = worldSize.y - texture->getSize().y / 2;

	for (int city = 0; city < 4; city++)
	{
		position.x = (city * (worldSize.x / 4)) + (worldSize.x / 8) - texture->getSize().x / 2;
		mCities[city].Initialize(texture, radarTexture, windowSize, worldSize, position);
	}
}

sf::FloatRect Cities::CityCollusion(int city)
{
	return *mCities[city].GetCollision();
}

Cities::Cities(void)
{
}
