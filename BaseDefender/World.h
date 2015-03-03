#ifndef WORLDH
#define WORLDH
#include "Cities.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>

class World
{
public:
	World(void);

	void Initialize(sf::Texture *TextureAttacker, sf::Texture *TextureCity, sf::Vector2u WindowSize, sf::Vector2f WorldBounds);
	void Update(sf::Time *Delta);
	void Draw(sf::RenderWindow *Window);

private:
	
};

#endif