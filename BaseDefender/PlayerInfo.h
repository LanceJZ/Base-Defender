#ifndef PlayerInfo_H
#define PlayerInfo_H
#include "Header.h"

class PlayerInfo
{
public:
	PlayerInfo();

	void SetActive(bool Active);
	void SetPosition(sf::Vector2f Position);
	void SetCollision(sf::FloatRect Collision);
	bool GetActive(void);
	sf::Vector2f GetPosision(void);
	sf::FloatRect GetCollision(void);

protected:

private:
	bool mActive;
	sf::Vector2f mPosition;
	sf::FloatRect mCollision;

};

#endif