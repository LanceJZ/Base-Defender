#pragma once
#include "EnemyRandomMover.h"

//This enemy breaks into five swarmer enemies (Schwärme) when hit.
class Unter :
	public EnemyRandomMover
{
public:
	Unter(void);

	void Update(sf::Time *delta);
	void Draw(sf::RenderWindow *window);
	void DrawOtherSide(sf::RenderWindow *window);
	void Initialize(sf::Texture *texture, sf::Texture *radarTexture, sf::Texture *shipExplosion, sf::Vector2u windowSize, sf::Vector2f worldSize);
	void PlayerPointer(std::shared_ptr<Player> playerSP);

	bool HitbyPlayerShot(void);

private:
	
};

