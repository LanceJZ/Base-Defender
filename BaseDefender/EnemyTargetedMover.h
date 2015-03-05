#pragma once
#include "Enemy.h"

class EnemyTargetedMover :
	public Enemy
{
public:
	EnemyTargetedMover(void);

protected:
	void Initialize(sf::Texture *texture, sf::Vector2u windowSize, sf::Vector2f worldSize);
	void Update(sf::Time *delta);
	void Setup(sf::Vector2f position, sf::Vector2f velocity);
	void ChaseTarget(sf::Vector2f *target);
	bool DoesMovementChange(void);

	float mMoveSpeed;
	float mNextMoveTime;
	float mMoveTimer;
	sf::Clock mClock;

private:
		
};

