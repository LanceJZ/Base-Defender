//Angreifer transforms into this enemy after a city that it was attacking is destroyed.
#ifndef Jäger_H
#define Jäger_H

#include "Enemy.h"
#include "EnemyRandomShooter.h"
#include "EnemyTargetedMover.h"

class Jäger :
	public EnemyTargetedMover, EnemyRandomShooter
{
public:
	Jäger(void);

	void Update(sf::Time *delta);
	void Draw(sf::RenderWindow *window);
	void DrawOtherSide(sf::RenderWindow *window);
	void Initialize(sf::Texture *texture, sf::Texture *radarTexture, sf::Texture *shotTexture, sf::Texture *shipExplosion,
		sf::Vector2u windowSize, sf::Vector2f worldSize);
	void PlayerPointer(std::shared_ptr<Player> playerSP);
	void Setup(sf::Vector2f position, sf::Vector2f velocity);
	void SetActive(bool active);
	bool GetActive(void);

};

#endif