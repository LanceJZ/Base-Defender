#include "Cities.h"

void Cities::Update(sf::Time *delta)
{
	for (int city = 0; city < 4; city++)
	{
		mCities[city].Update(delta);
	}
}

void Cities::Draw(sf::RenderWindow *window)
{
	for (int city = 0; city < 4; city++)
	{
		mCities[city].Draw(window);
	}
}

void Cities::Initialize(sf::Texture *texture, sf::Vector2u windowSize, sf::Vector2f worldSize)
{
	sf::Vector2f position;

	position.y = worldSize.y - texture->getSize().y / 2;

	//CityBases[City].X = (City * (Data.Global.GameData.WorldWidth / 2)) - Data.Global.GameData.WorldWidth / 1.33f;

	for (int city = 0; city < 4; city++)
	{
		//mCities[city] = new City();

		position.x = (city * (worldSize.x / 4)) + (worldSize.x / 8) - texture->getSize().x / 2;
		mCities[city].Initialize(texture, windowSize, worldSize, position);
	}
}

sf::FloatRect Cities::CityCollusion(int city)
{
	return *mCities[city].GetCollision();
}

Cities::Cities(void)
{
}
