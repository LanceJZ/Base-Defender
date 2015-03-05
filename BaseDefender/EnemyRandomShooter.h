#ifndef EnemyRandomShooter_H
#define EnemyRandomShooter_H
#include "EnemyShot.h"
#include "Player.h"

class EnemyRandomShooter :
	Common
{
public:
	EnemyRandomShooter(void);
		
protected:
	float mShotSpeed;
	float mNextShotTime;
	float mShotTimer;

	sf::Clock mClock;

	std::vector<std::unique_ptr<EnemyShot>> mShots;

	void Update(sf::Time *delta, sf::Vector2f *position);
	void Draw(sf::RenderWindow *window);
	void DrawOtherSide(sf::RenderWindow *window);
	void Initialize(sf::Texture *texture, sf::Vector2i offset, sf::Vector2u windowSize, sf::Vector2f worldSize);
	void FireShot(sf::Vector2f *position);
	void PlayerPointer(std::shared_ptr<Player> playerSP);
	bool GetActive(void);
	void SetActive(bool active);

private:
	std::shared_ptr<Player> pPlayer;

	bool mActive;
	float mShotTime;

	sf::Texture *mShotTexture;
	sf::Vector2u mWindowSize;
	sf::Vector2f mWorldSize;
	sf::Vector2i mOffset;

	sf::Vector2f RandomShotVector(void);

	int SpawnNewShot(void);

	void SetupShot(sf::Vector2f position, int shot);
};
#endif