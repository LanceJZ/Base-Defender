#ifndef CITIESH
#define CITIESH
#include "City.h"
#include "Header.h"

class Cities
{
public:
	Cities(void);	
	
	void Initialize(sf::Texture *texture, sf::Texture *textureDamaged1, sf::Texture *textureDamaged2, sf::Texture *textureDamaged3,
		sf::Texture *textureDamaged4, sf::Texture *textureDistroyed, sf::Texture *radarTexture, sf::Texture *radarAlertTexture, sf::Texture *radarDistroyedTexture,
		sf::Vector2u windowSize, sf::Vector2f worldSize);
	void Update(sf::Time *delta, float *playerX);
	void Draw(sf::RenderWindow *window);
	void DrawRadar(sf::RenderWindow *window);
	void BombHitCity(int cityNumber);
	bool GetCityDistroyed(int cityNumber);
	sf::FloatRect CityCollusion(int city);

private:
	City mCities[4];
};

#endif