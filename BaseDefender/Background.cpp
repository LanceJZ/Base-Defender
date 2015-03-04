#include "Background.h"

void Background::Update(void)
{

}

void Background::Draw(sf::RenderWindow *Window)
{
	Window->draw(*mStarsBackground);
	Window->draw(mLine);
}

void Background::Initialize(sf::Texture *StarTexture, sf::Vector2u WindowSize, sf::Vector2f WorldBounds)
{
	mWindowSize = WindowSize;
	mWorldBounds = WorldBounds;
	StarTexture->setRepeated(true);
	mStarsBackground->setTextureRect(sf::IntRect(0, 0, int(mWorldBounds.x), int(mWorldBounds.y)));
	mStarsBackground->setTexture(*StarTexture);
	mStarsBackground->setPosition(0.0f, 60.0f);
}

void Background::InitializeLine(sf::Texture *LineTexture)
{
	mLine.setTexture(*LineTexture);
	mLine.setPosition(mWorldBounds.x - 10.0f, 60.0f);
}

Background::Background()
{
	mStarsBackground = new sf::Sprite();
}