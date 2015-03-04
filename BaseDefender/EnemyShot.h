#ifndef EnemyShot_H
#define EnemyShot_H
#include "Enemy.h"

class EnemyShot :
	public Enemy
{
public:
	EnemyShot(void);

	void Update(sf::Time *delta);
	void Draw(sf::RenderWindow *window);
	void DrawOtherSide(sf::RenderWindow *window);
	void Initialize(sf::Texture *texture, sf::Vector2u windowSize, sf::Vector2f worldSize);
	void PlayerPointer(std::shared_ptr<Player> playerSP);
	void FireShot(sf::Vector2f position);

private:
	float mTimerAmount;
	float mTimerLife;

	void ShotTimer(void);
};

#endif