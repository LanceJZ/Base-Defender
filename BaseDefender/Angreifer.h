//Enemy that seeks out city while randomly shooting. Common.
#ifndef Angreifer_H
#define Angreifer_H

#include "EnemyRandomMover.h"
#include "EnemyRandomShooter.h"

class Angreifer :
	public EnemyRandomMover, EnemyRandomShooter
{
public:
	Angreifer(void);

	void Update(sf::Time *delta);
	void Draw(sf::RenderWindow *window);
	void DrawOtherSide(sf::RenderWindow *window);
	void Initialize(sf::Texture *texture, sf::Texture *radarTexture, sf::Texture *shotTexture, sf::Texture *shipExplosion,
		sf::Vector2u windowSize, sf::Vector2f worldSize);
	void Setup(sf::Vector2f position, sf::Vector2f velocity);
	void PlayerPointer(std::shared_ptr<Player> playerSP);
	void SetActive(bool active);
	bool GetActive(void);
	int CityNumber(void);

private:	
};
#endif