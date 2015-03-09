#include "City.h"

void City::Update(sf::Time *delta, float *playerX)
{
	UpdateRadar(*playerX);

	if (mAlertOn)
		Alert();
}

void City::Draw(sf::RenderWindow *window)
{
	Entity::Draw(window);
}

void City::DrawRadar(sf::RenderWindow *window)
{
	window->draw(*mRadar);
}

void City::Initialize(sf::Vector2f *position, sf::Texture *texture, sf::Texture *textureDamaged1, sf::Texture *textureDamaged2, sf::Texture *textureDamaged3,
	sf::Texture *textureDamaged4, sf::Texture *textureDistroyed, sf::Texture *radarTexture, sf::Texture *radarAlertTexture, sf::Texture *radarDistroyedTexture,
	sf::Vector2u windowSize, sf::Vector2f worldSize)
{
	Entity::Initialize(texture, windowSize, worldSize);
	Entity::SetPosition(position);
	Entity::UpdateCollusionPosition();
	mRadar->setTexture(*radarTexture);
	mCity = texture;
	mCityDamaged1 = textureDamaged1;
	mCityDamaged2 = textureDamaged2;
	mCityDamaged3 = textureDamaged3;
	mCityDamaged4 = textureDamaged4;
	mCityDistroyed = textureDistroyed;
	mRadarCity = radarTexture;
	mRadarCityAlert = radarAlertTexture;
	mRadarCityDistroyed = radarDistroyedTexture;
	m_Active = true;
	mAlertOn = false;
	mDistroyed = false;
	mAmountAlertTimer = 3;
	mHitPoints = 100;
}

void City::Alert(void)
{
	if (mTimerAlert < mClock.getElapsedTime().asSeconds() && mRadarAlert)
	{
		mTimerAlert = Common::ResetTimer(mAmountAlertTimer, mAmountAlertTimer / 2);
		mRadar->setTexture(*mRadarCity);
		mRadarAlert = false;
	}
	else if (mTimerAlert < mClock.getElapsedTime().asSeconds() && !mRadarAlert)
	{
		mTimerAlert = Common::ResetTimer(mAmountAlertTimer, mAmountAlertTimer / 2);
		mRadar->setTexture(*mRadarCityAlert);
		mRadarAlert = true;
	}
}

void City::HitByBomb(void)
{
	if (!mDistroyed)
	{
		mHitPoints -= 10;
		mAlertOn = true;
		mRadar->setTexture(*mRadarCityAlert);
		mTimerAlert = Common::ResetTimer(mAmountAlertTimer, mAmountAlertTimer / 2);

		if (mHitPoints < 10)
		{
			mDistroyed = true;
			mAlertOn = false;
			Entity::SetTexture(mCityDistroyed);
			mRadar->setTexture(*mRadarCityDistroyed);
		}
		else if (mHitPoints < 20)
			Entity::SetTexture(mCityDamaged4);
		else if (mHitPoints < 40)
			Entity::SetTexture(mCityDamaged3);
		else if (mHitPoints < 60)
			Entity::SetTexture(mCityDamaged2);
		else if (mHitPoints < 80)
			Entity::SetTexture(mCityDamaged1);
	}
}

bool City::GetDistroyed(void)
{
	return mDistroyed;
}

City::City(void)
{
	mRadar = new sf::Sprite();
}

void City::UpdateRadar(float playerX)
{
	playerX += 64;
	float radarX = (Entity::GetPosition()->x - playerX) *0.1f;

	playerX *= 0.1f;
	radarX += float(m_WindowSize.x * 2) * 0.1f;
	radarX += float(int(m_WindowSize.x * 0.5f) - 256);

	if (radarX > 895)
		radarX -= 512;

	if (radarX < 383)
		radarX += 512;

	mRadar->setPosition(sf::Vector2f(radarX, float(int(m_WindowSize.y) - mRadar->getTextureRect().height)));
}