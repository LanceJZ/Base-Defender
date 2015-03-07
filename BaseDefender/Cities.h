#ifndef CITIESH
#define CITIESH
#include "City.h"
#include "Header.h"

class Cities
{
public:
	Cities(void);	
	
	void Initialize(sf::Texture *texture, sf::Texture *radarTexture, sf::Vector2u windowSize, sf::Vector2f worldSize);
	void Update(sf::Time *delta, float *playerX);
	void Draw(sf::RenderWindow *window);
	void DrawRadar(sf::RenderWindow *window);
	sf::FloatRect CityCollusion(int city);

private:
	City mCities[4];
};

#endif