#pragma once
#include "Player.h"

class EnemyCityBomb :
	public Entity
{
public:
	EnemyCityBomb(void);

	void Update(sf::Time *delta);
	void Draw(sf::RenderWindow *window);
	void DrawOtherSide(sf::RenderWindow *window);
	void Initialize(sf::Texture *texture, sf::Texture *bombExplosion, sf::Vector2u windowSize, sf::Vector2f worldSize);
	void PlayerPointer(std::shared_ptr<Player> playerSP);
	void CityInfo(sf::Vector2f cityPosition, float cityWidth);
	void DropBomb(sf::Vector2f position);

private:
	sf::FloatRect *mCityCollision;
	sf::Sprite *mBombExplosion;
	std::shared_ptr<Player> pPlayer;

	float mExplodeTimerAmount;
	float mExplodeTimer;
	bool mExploding;

	void HitTarget(void);
	void Explode(void);
	void ExplodeTimer(void);

};

