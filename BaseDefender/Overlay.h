#ifndef OVERLAYH
#define OVERLAYH
#include <SFML/Graphics.hpp>

class Overlay
{
public:
	Overlay(void);

	void Update(void);
	void Draw(sf::RenderWindow *Window);
	void Initialize(sf::Texture *OverlayTexture);

private:
	sf::Sprite *mOverlay;
};

#endif