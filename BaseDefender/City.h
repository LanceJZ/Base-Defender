#ifndef CITYH
#define CITYH

#include "Entity.h"

namespace CityTextures
{
	enum ID
	{
		New,
		Damaged10,
		Damaged25,
		Damaged50,
		Damaged75,
		Distroyed,
		Shield
	};
}

class City :
	public Entity
{
public:
	City(void);
	
	void Initialize(sf::Texture *texture, sf::Vector2u windowSize, sf::Vector2f worldSize, sf::Vector2f position);
	void Update(sf::Time *delta);
	void Draw(sf::RenderWindow *window);

private:

};

#endif