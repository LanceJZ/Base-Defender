#pragma once
#include "Angreifer.h"
#include "AngreiferFoundCity.h"
#include "Angriff_auf_Stadt.h"
#include "Cities.h"
#include "Common.h"

class EnemyCitySpawner :
	public Common
{
public:
	EnemyCitySpawner(void);

protected:
	void Update(sf::Time *delta);
	void Draw(sf::RenderWindow *window);
	void DrawOtherSide(sf::RenderWindow *window);
	void Initialize(sf::Texture *angreiferTexture, sf::Texture *angreiferShotTexture, sf::Texture *stadt_AngreiferTexture, sf::Texture *angreiferFCTexture,
		sf::Texture *bombTexture, sf::Texture *bombExplosion, sf::Vector2u windowSize, sf::Vector2f worldBounds);
	void PlayerPointer(std::shared_ptr<Player> playerSP);
	void CityPointer(std::shared_ptr<Cities> citySP);
	void SpawnAngreifers(void);

private:
	std::shared_ptr<Player> pPlayer;
	std::shared_ptr<Cities> pCities;
	std::vector<std::unique_ptr<Angreifer>> mAngreifers;
	std::vector<std::unique_ptr<AngreiferFoundCity>> mAngreiferFCs;
	std::vector<std::unique_ptr<Angriff_auf_Stadt>> mAngriff_auf_Stadts;

	sf::Vector2u mWindowSize;
	sf::Vector2f mWorldSize;
	sf::Texture *mAngreiferTexture;
	sf::Texture *mAngreiferShotTexture;
	sf::Texture *mStadt_AngreiferTexture;
	sf::Texture *mAngreiferFCTexture;
	sf::Texture *mBombTexture;
	sf::Texture *mBombExplosion;

	int mNumberOfAngreifers;
	float mAngreiferSpawnTimer;
	float mAngreiferSpawnTimerAmount;
	float mCityHuntTimer;
	float mCityHuntTimerAmount;

	void SendAngreiferToCity(void);
	void SpawnAngriff_auf_Stadt(sf::Vector2f postion, sf::Vector2f velocity, int cityAttacking, sf::Vector2f cityPosition);
	void SpawnmAngreiferFC(sf::Vector2f position, sf::Vector2f velocity);
};

