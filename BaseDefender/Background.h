#ifndef BACKGROUNDH
#define BACKGROUNDH
#include <SFML/Graphics.hpp>

class Background
{
public:
	Background(void);

	void Update(void);
	void Draw(sf::RenderWindow *Window);
	void Initialize(sf::Texture *StarTexture, sf::Vector2u WindowSize, sf::Vector2f WorldBounds);
	void InitializeLine(sf::Texture *LineTexture);

private:
	sf::Vector2u mWindowSize;
	sf::Vector2f mWorldBounds;

	sf::Sprite *mStarsBackground;
	sf::Sprite mLine;
};

#endif