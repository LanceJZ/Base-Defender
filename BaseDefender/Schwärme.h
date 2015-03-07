#pragma once
#include "EnemyTargetedMover.h"
#include "EnemyRandomShooter.h"

//The enemy that swarms around the player after they hit a Unter.
class Schwärme :
	public EnemyTargetedMover, EnemyRandomShooter
{
public:
	Schwärme(void);

	void Update(sf::Time *delta);
	void Draw(sf::RenderWindow *window);
	void DrawOtherSide(sf::RenderWindow *window);
	void Initialize(sf::Texture *texture, sf::Texture *radarTexture, sf::Texture *shotTexture, sf::Texture *shipExplosion,
		sf::Vector2u windowSize, sf::Vector2f worldSize);
	void PlayerPointer(std::shared_ptr<Player> playerSP);
	void Setup(sf::Vector2f position, sf::Vector2f velocity);
	void SetActive(bool active);
	bool GetActive(void);

private:

};

