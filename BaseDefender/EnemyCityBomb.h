#pragma once
#include "Enemy.h"
#include "Cities.h"

class EnemyCityBomb :
	public Enemy
{
public:
	EnemyCityBomb(void);

	void Update(sf::Time *delta);
	void Draw(sf::RenderWindow *window);
	void DrawOtherSide(sf::RenderWindow *window);
	void Initialize(sf::Texture *texture, sf::Texture *bombExplosion, sf::Vector2u windowSize, sf::Vector2f worldSize);
	void PlayerPointer(std::shared_ptr<Player> playerSP);
	void CityInfo(sf::Vector2f cityPosition, float cityWidth, int cityNumber);
	void DropBomb(sf::Vector2f position);
	void CityPointer(std::shared_ptr<Cities> citySP);

private:
	sf::FloatRect *mCityCollision;
	std::shared_ptr<Cities> pCities;

	float mExplodeTimerAmount;
	int mCityBombing;

	void HitTarget(void);
};

