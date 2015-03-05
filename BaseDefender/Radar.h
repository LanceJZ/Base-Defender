#pragma once
#include "Common.h"

class Radar :
	public Common
{
public:
	Radar(void);

	void Update(sf::Time *delta);
	void Draw(sf::RenderWindow *window);
	void DrawOtherSide(sf::RenderWindow *window);

private:

};

