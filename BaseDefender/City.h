#ifndef CITYH
#define CITYH

#include "Entity.h"

namespace CityTextures
{
	enum ID
	{
		New,
		Damaged10,
		Damaged25,
		Damaged50,
		Damaged75,
		Distroyed,
		Shield
	};
}

class City :
	public Entity
{
public:
	City(void);
	
	void Initialize(sf::Vector2f *position, sf::Texture *texture, sf::Texture *textureDamaged1, sf::Texture *textureDamaged2, sf::Texture *textureDamaged3,
		sf::Texture *textureDamaged4, sf::Texture *textureDistroyed, sf::Texture *radarTexture, sf::Texture *radarAlertTexture, sf::Texture *radarDistroyedTexture,
		sf::Vector2u windowSize, sf::Vector2f worldSize);
	void Update(sf::Time *delta, float *playerX);
	void Draw(sf::RenderWindow *window);
	void DrawRadar(sf::RenderWindow *window);
	void HitByBomb(void);
	void Alert(void);
	bool GetDistroyed(void);

private:
	sf::Sprite *mRadar;
	sf::Texture *mCity;
	sf::Texture *mCityDamaged1;
	sf::Texture *mCityDamaged2;
	sf::Texture *mCityDamaged3;
	sf::Texture *mCityDamaged4;
	sf::Texture *mCityDistroyed;
	sf::Texture *mRadarCity;
	sf::Texture *mRadarCityAlert;
	sf::Texture *mRadarCityDistroyed;

	float mHitPoints;
	float mTimerAlert;
	float mAmountAlertTimer;
	bool mAlertOn;
	bool mRadarAlert;
	bool mDistroyed;

	void UpdateRadar(float playerX);
};

#endif