#pragma once
#include "Player.h"

class Enemy :
	public Entity
{
public:
	Enemy(void);

	void Update(sf::Time *delta);
	void Draw(sf::RenderWindow *window);
	void DrawOtherSide(sf::RenderWindow *window);
	bool HitbyPlayerShot(void);
	bool HitPlayer(void);

	void Initialize(sf::Texture *explosionTexture);

protected:
	std::shared_ptr<Player> pPlayer;
	float mMaxVolicityY;
	float mMaxVolicityX;

	void CheckVelocity(void);
	void Explode(sf::Vector2f position, float duration);

private:
	sf::Sprite *mExplosion;

	bool mExploding;
	float mTimerExplode;
};

