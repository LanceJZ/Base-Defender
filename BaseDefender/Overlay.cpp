#include "Overlay.h"


Overlay::Overlay()
{
	mOverlay = new sf::Sprite();
}

void Overlay::Draw(sf::RenderWindow *window)
{
	window->draw(*mOverlay);
}

void Overlay::Initialize(sf::Texture *OverlayTexture)
{
	mOverlay->setTexture(*OverlayTexture);
}
