#pragma once
#include "EnemyTargetedMover.h"
#include "EnemyRandomShooter.h"
#include "Cities.h"
#include "EnemyCityBomb.h"

//AngreiferFC is swapped into this to bomb city.
class Angriff_auf_Stadt :
	public EnemyTargetedMover, EnemyRandomShooter
{
public:
	Angriff_auf_Stadt(void);

	void Update(sf::Time *delta);
	void Draw(sf::RenderWindow *window);
	void DrawOtherSide(sf::RenderWindow *window);
	void Initialize(sf::Texture *texture, sf::Texture *radarTexture, sf::Texture *shotTexture, sf::Texture *bombTexture, sf::Texture *bombExplosion, sf::Texture *shipExplosion,
		sf::Vector2u windowSize, sf::Vector2f worldSize);
	void Setup(sf::Vector2f position, sf::Vector2f velocity, int cityNumber, sf::Vector2f cityPosition);
	void PlayerPointer(std::shared_ptr<Player> playerSP);
	void CityPointer(std::shared_ptr<Cities> citySP);
	bool GetCityDistroyed(void);

private:
	std::shared_ptr<Cities> pCities;
	EnemyCityBomb * mBomb;
	sf::Texture *mBombTexture;
	sf::Vector2f mNextTargetPosition;
	sf::Vector2f mBombPosition;
	sf::Vector2f mTargetCity;

	int mBombCityNumber;
	float mBombDropAmount;
	float mBombDropTimer;

	void DropBomb(void);
};