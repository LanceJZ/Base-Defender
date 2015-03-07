#include "Radar.h"

void Radar::Update(sf::Time *delta)
{
}

void Radar::Draw(sf::RenderWindow *window)
{
	window->draw(*mRadarBackground);
}

void Radar::Initialize(sf::Texture *radarTexture, sf::Vector2u windowSize)
{
	mRadarBackground->setTexture(*radarTexture);
	mRadarBackground->setPosition(float(int(windowSize.x *0.5f) - mRadarBackground->getTextureRect().width * 0.5f), float(int(windowSize.y) - mRadarBackground->getTextureRect().height));
}

Radar::Radar(void)
{
	mRadarBackground = new sf::Sprite();
}

