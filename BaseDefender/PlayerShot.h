#ifndef PlayerShot_H
#define PlayerShot_H
#include "Entity.h"

class PlayerShot :
	public Entity
{
public:
	PlayerShot();

	sf::Vector2f *GetPosition(void);

	bool GetActive(void);

	void Draw(sf::RenderWindow *Window);
	void Update(sf::Time *Delta);
	void Initialize(sf::Texture *Texture, sf::Vector2u WindowSize, sf::Vector2f WorldBounds);
	void Fire(sf::Vector2f Position, sf::Vector2f Velocity);
	void Hit(void);

private:
	float mMoveSpeed;
	float mShotActiveTime;
	float mShotTimer;

	float ShotTime(void);
	bool ShotOutOfTime(void);
};

#endif