#ifndef EnemySpawner_H
#define EnemySpawner_H
#include "Minenleger.h"
#include "Unter.h"
#include "Schw�rme.h"
#include "EnemyCitySpawner.h"

class EnemySpawner :
	public EnemyCitySpawner
{
public:
	EnemySpawner(void);

	void Update(sf::Time *delta);
	void Draw(sf::RenderWindow *window);
	void DrawOtherSide(sf::RenderWindow *window);
	void DrawRadar(sf::RenderWindow *window);
	void Initialize(sf::Texture *minenlegerTexture,	sf::Texture *mineTexture, sf::Texture *unterTexture, sf::Texture *schw�rmeTexture, sf::Texture *shotTexture, sf::Texture *enemyExplosion,
		sf::Vector2u windowSize, sf::Vector2f worldBounds);
	void InitializeCityEnemys(sf::Texture *angreiferTexture, sf::Texture *stadt_AngreiferTexture, sf::Texture *angreiferTextureFC,
		sf::Texture *j�gerTexture, sf::Texture *bombTexture, sf::Texture *bombExplosion);
	void InitializeRadar(sf::Texture *minenlegerRadarTexture, sf::Texture *unterRadarTexture, sf::Texture *schw�rmeRadarTexture);
	void InitializeCityEnemyRadar(sf::Texture *angreiferRadarTexture, sf::Texture *j�gerRadarTexture);
	void PlayerPointer(std::shared_ptr<Player> playerSP);
	void CityPointer(std::shared_ptr<Cities> citySP);

private:
	std::shared_ptr<Player> pPlayer;
	std::shared_ptr<Cities> pCities;
	sf::Vector2u mWindowSize;
	sf::Vector2f mWorldSize;
	sf::Texture *mMinenlegerTexture;
	sf::Texture *mMinenlegerRadarTexture;
	sf::Texture *mMineTexture;
	sf::Texture *mUnterTexture;
	sf::Texture *mUnterRadarTexture;
	sf::Texture *mSchw�rmeTexture;
	sf::Texture *mSchw�rmeRadarTexture;
	sf::Texture *mShotTexture;
	sf::Texture *mEnemyExplosion;

	std::vector<std::unique_ptr<Minenleger>> mMinenlegers;
	std::vector<std::unique_ptr<Unter>> mUnters;
	std::vector<std::unique_ptr<Schw�rme>> mSchw�rmes;
	
	int mNumberOfAngreifers;
	int mNumberOfMinenlegers;
	int mNumberOfUnters;
	float mAngreiferSpawnTimer;
	float mAngreiferSpawnTimerAmount;
	float mCityHuntTimer;
	float mCityHuntTimerAmount;

	void SpawnMinenlegers(void);
	void SpawnUnters(void);
	void IsUnterHit(int ship);
	void SpawnSchw�rmes(sf::Vector2f position);
	void SpawnStadt_Angreifer(sf::Vector2f postion, int cityAttacking);	
};
#endif