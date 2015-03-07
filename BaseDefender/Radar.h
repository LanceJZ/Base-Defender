#pragma once
#include "Common.h"

class Radar :
	public Common
{
public:
	Radar(void);

	void Update(sf::Time *delta);
	void Draw(sf::RenderWindow *window);
	void Initialize(sf::Texture *radarTexture, sf::Vector2u windowSize);

private:
	sf::Sprite *mRadarBackground;
	float *mPlayerX;
};

