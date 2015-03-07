#pragma once
#include "EnemyTargetedMover.h"
#include "EnemyRandomShooter.h"
#include "Cities.h"
//This class is a mode for this ship type that moves it to the city that was assigned to it, spawned to do one thing. 
//When it moves to its city, just over the top, IPTB becomes true telling
//the enemy spawn class to disable it, and spawn the city bomber mode in its place.
//Separating every mode will make the code easier to maintain.

class AngreiferFoundCity :
	public EnemyTargetedMover, EnemyRandomShooter
{
public:
	AngreiferFoundCity(void);

	void Update(sf::Time *delta);
	void Draw(sf::RenderWindow *window);
	void DrawOtherSide(sf::RenderWindow *window);
	void Initialize(sf::Texture *texture, sf::Texture *radarTexture, sf::Texture *shotTexture, sf::Texture *shipExplosion,
		sf::Vector2u windowSize, sf::Vector2f worldSize);
	void Setup(sf::Vector2f position, sf::Vector2f velocity,int cityNumber, sf::Vector2f cityPosition);
	void PlayerPointer(std::shared_ptr<Player> playerSP);
	void CityPointer(std::shared_ptr<Cities> citySP);
	bool InPositionToBombCity(void); //This lets EnemySpaner know this one is ready to bomb so that it can be turned into a city bomber.
	int GetCityNumber(void);
	sf::Vector2f GetCityTarget(void);

private:
	std::shared_ptr<Cities> pCities;

	sf::Vector2f mNextTargetPosition;
	sf::Vector2f mTargetCity;
	sf::FloatRect mNextTargetLocation; //When collides, make next location position.

	int mBombCityNumber;

	sf::Vector2f NextTarget(void);
};

