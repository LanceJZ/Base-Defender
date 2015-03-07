#pragma once
#include "EnemyMineLayer.h"

// Lays mines as it moves mostly on the y axis, and keeps the same vector and velocity it started with. The mines stay active for about thirty seconds.
class Minenleger :
	public EnemyMineLayer
{
public:
	Minenleger(void);

	void Update(sf::Time *delta);
	void Draw(sf::RenderWindow *window);
	void DrawOtherSide(sf::RenderWindow *window);
	void Initialize(sf::Texture *texture, sf::Texture *radarTexture, sf::Texture *bombTexture, sf::Texture *shipExplosion,
		sf::Vector2u windowSize, sf::Vector2f worldSize);
	void Setup(sf::Vector2f position, sf::Vector2f velocity);
	void PlayerPointer(std::shared_ptr<Player> playerSP);

private:
	void CheckEdge(void);
};

