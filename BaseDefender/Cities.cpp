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

void Cities::Initialize(sf::Texture *texture, sf::Texture *textureDamaged1, sf::Texture *textureDamaged2, sf::Texture *textureDamaged3,
	sf::Texture *textureDamaged4, sf::Texture *textureDistroyed, sf::Texture *radarTexture, sf::Texture *radarAlertTexture, sf::Texture *radarDistroyedTexture,
	sf::Vector2u windowSize, sf::Vector2f worldSize)
{
	sf::Vector2f position;

	position.y = worldSize.y - texture->getSize().y / 2;

	for (int city = 0; city < 4; city++)
	{
		position.x = (city * (worldSize.x / 4)) + (worldSize.x / 8) - texture->getSize().x / 2;
		mCities[city].Initialize(&position, texture, textureDamaged1, textureDamaged2, textureDamaged3,
			textureDamaged4, textureDistroyed, radarTexture, radarAlertTexture, radarDistroyedTexture,
			windowSize, worldSize);
	}
}

void Cities::BombHitCity(int cityNumber)
{
	mCities[cityNumber].HitByBomb();
}

bool Cities::GetCityDistroyed(int cityNumber)
{
	return mCities[cityNumber].GetDistroyed();
}

sf::FloatRect Cities::CityCollusion(int city)
{
	return *mCities[city].GetCollision();
}

Cities::Cities(void)
{
}
