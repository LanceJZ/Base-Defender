#ifndef Game_H
#define Game_H

#include "ResourceHolder.hpp"
#include "Player.h"
#include "Background.h"
#include "Overlay.h"
#include "Radar.h"
#include "Cities.h"

#include "EnemySpawner.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

#include <memory>

namespace Textures
{
	enum ID
	{
		Player,
		PlayerRadar,
		PlayerShot,
		PlayerThrust,
		PlayerShieldOver,
		PlayerShieldUnder,
		Background,
		BackgroundLine,
		Overlay,
		Radar,
		City,
		CityRadar,
		Attacker,
		AttackerRadar,
		AttackerShot,
		AttackerBomber,
		AttackerFC,
		MineLayer,
		MineLayerRadar,
		Mine,
		Pod,
		PodRadar,
		Swarmer,
		SwarmerRadar,
		EnemyExplosion,
		Bomb,
		BombExplosion,
	};
}

class Game
{
public:
	Game(void);

	void Initialize(void); //Initialize game, load content.
	void Run(void);

private:
	bool mSeeLeftSide;
	bool mSeeRightSide;
	float mPlayerCenterX;
	float mWorldPlayerXMax;
	float mWorldPlayerXMin;

	//Player *pPlayer;

	sf::Vector2f mWorldSize;
	sf::RenderWindow *mWindow;
	sf::View *mWorldView;
	sf::View *mWorldOthersideView;

	void ProcessInput(sf::Event *event);
	void Update(sf::Time *delta);
	void Draw(void);
};

#endif