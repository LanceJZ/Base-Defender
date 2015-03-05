#ifndef EnemyMineLayer_H
#define EnemyMineLayer_H
#include "EnemyMine.h"
#include "Enemy.h"

//Enemies that lay mines.
class EnemyMineLayer :
	public Enemy
{
public:
	EnemyMineLayer(void);

	void Update(sf::Time *delta);
	void Draw(sf::RenderWindow *window);
	void DrawOtherSide(sf::RenderWindow *window);
	void Initialize(sf::Texture *texture, sf::Vector2u windowSize, sf::Vector2f worldSize);
	void LayMine(sf::Vector2f position);

protected:
	std::vector<std::unique_ptr<EnemyMine>> mMines;
	sf::Clock mClock;
	float mMineLaySpeed;

private:
	float mNextMineTimer;

	sf::Texture *mMineTexture;
	sf::Vector2u mWindowSize;
	sf::Vector2f mWorldSize;

	int SpawnNewMine(void);

	void SetupMine(sf::Vector2f position, int shot);
};

#endif