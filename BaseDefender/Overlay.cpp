#include "Overlay.h"


Overlay::Overlay()
{
	mOverlay = new sf::Sprite();
}

void Overlay::Draw(sf::RenderWindow *Window)
{
	Window->setView(Window->getDefaultView());
	Window->draw(*mOverlay);
}

void Overlay::Initialize(sf::Texture *OverlayTexture)
{
	mOverlay->setTexture(*OverlayTexture);
}
