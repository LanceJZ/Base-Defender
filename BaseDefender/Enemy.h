#pragma once
#include "Player.h"

class Enemy :
	public Entity
{
public:
	Enemy(void);

	bool HitbyPlayerShot(void);

protected:
	std::shared_ptr<Player> pPlayer;
	float mMaxVolicityY;
	float mMaxVolicityX;

	void CheckVelocity(void);

private:
};

