#ifndef EnemyRandomMover_H
#define EnemyRandomMover_H
#include "Enemy.h"

class EnemyRandomMover :
	public Enemy
{
public:
	EnemyRandomMover(void);

	void Setup(sf::Vector2f position, sf::Vector2f velocity);

protected:
	void Initialize(sf::Texture *texture, sf::Vector2u windowSize, sf::Vector2f worldSize);
	void Update(sf::Time *delta);

	float mMoveSpeed;
	float mNextMoveTime;
	float mMoveTimer;
	sf::Clock mClock;

private:
	void ChangeMovement(void);
	bool DoesMovementChange(void);
};
#endif