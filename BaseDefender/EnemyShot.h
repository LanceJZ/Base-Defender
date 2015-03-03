#ifndef EnemyShot_H
#define EnemyShot_H
#include "Player.h"

class EnemyShot :
	public Entity
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
	std::shared_ptr<Player> pPlayer;

	float mTimerAmount;
	float mTimerLife;

	bool HitPlayer(void);

	void ShotTimer(void);
};

#endif