#pragma once
#include "Enemy.h"
//The mine that the mine layer drops.

class EnemyMine :
	public Enemy
{
public:
	EnemyMine(void);

	void Update(sf::Time *delta);
	void Draw(sf::RenderWindow *window);
	void DrawOtherSide(sf::RenderWindow *window);
	void Initialize(sf::Texture *texture, sf::Vector2u windowSize, sf::Vector2f worldSize);
	void PlayerPointer(std::shared_ptr<Player> playerSP);
	void LayMine(sf::Vector2f position);

private:
	float mTimerAmount;
	float mTimerLife;

	void MineTimer(void);

};

