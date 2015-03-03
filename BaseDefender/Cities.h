#ifndef CITIESH
#define CITIESH
#include "City.h"
#include "Header.h"

class Cities
{
public:
	Cities(void);	
	
	void Initialize(sf::Texture *texture, sf::Vector2u windowSize, sf::Vector2f worldSize);
	void Update(sf::Time *delta);
	void Draw(sf::RenderWindow *window);
	sf::FloatRect CityCollusion(int city);

private:
	City mCities[4];
};

#endif