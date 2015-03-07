#ifndef PLAYER_H
#define PLAYER_H
#include "PlayerShot.h"

class Player :
	public Entity
{
public:
	Player(void);
	
	void Draw(sf::RenderWindow *window);
	void DrawRadar(sf::RenderWindow *window);
	void Update(sf::Time *delta);
	void Events(sf::Event *event);
	void Initialize(sf::Texture *Texture, sf::Texture *RadarTexture, sf::Texture *ShotTexture, sf::Texture *ThrustTexture, sf::Texture *ShieldOverTexture, sf::Texture *ShieldUnderTexture,
		sf::Vector2u WindowSize, sf::Vector2f WorldBounds);
	void ShotHit(size_t shot);
	void PlayerHit(void);

	bool ShotActive(size_t shot);
	size_t ShotCount(void);
	sf::Vector2f *ShotPosition(size_t shot);
	sf::FloatRect *ShotCollision(size_t shot);

private:
	std::vector<std::unique_ptr<PlayerShot>> mShots;
	sf::Texture *m_ShotTexture;
	sf::Sprite *mThrust;
	sf::Sprite *mShieldUnder;
	sf::Sprite *mShieldOver;
	sf::Sprite *mRadar;
	sf::Vector2f mTextureSize; //So ship texture can be flipped on sprite using Texture Rectangle.
	sf::Vector2f mThrustTextureSize; //This is for flipping this texture for the sprite.
	sf::Vector2f mMaxVol;

	bool mFlipped;  //Flips the sprite on the horizontal axis
	bool mThrustOn; //Draws the thrust sprite
	bool mShieldOn; //Draws the shield sprite
	bool mAccelerating; //If the right or left key is pressed.
	bool mAltitude; //If the up or down key is pressed.
	float mShieldDisplayTimerAmount;
	float mShieldDisplayTimer;

	void CheckVelocity(void);
	void FireShot(void);
	void SetThrust(void);
	void SetShield(void);
};

#endif