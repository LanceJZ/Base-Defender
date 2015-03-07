#include "AngreiferFoundCity.h"

void AngreiferFoundCity::Update(sf::Time *delta)
{
	if (Entity::m_Active)
	{
		if (EnemyTargetedMover::DoesMovementChange())
			EnemyTargetedMover::ChaseTarget(&mNextTargetPosition);

		if (Entity::GetCollision()->intersects(mNextTargetLocation))
			mNextTargetPosition = NextTarget();
	}

	EnemyRandomShooter::SetActive(m_Active);
	EnemyRandomShooter::Update(delta, Entity::GetPosition());
	EnemyTargetedMover::Update(delta);
}

void AngreiferFoundCity::Draw(sf::RenderWindow *window)
{
	Enemy::Draw(window);
	EnemyRandomShooter::Draw(window);
}

void AngreiferFoundCity::DrawOtherSide(sf::RenderWindow *window)
{
	Enemy::DrawOtherSide(window);
	EnemyRandomShooter::DrawOtherSide(window);
}

void AngreiferFoundCity::Initialize(sf::Texture *texture, sf::Texture *radarTexture, sf::Texture *shotTexture, sf::Texture *shipExplosion,
	sf::Vector2u windowSize, sf::Vector2f worldSize)
{
	EnemyRandomShooter::Initialize(shotTexture, sf::Vector2i(texture->getSize().x / 2, texture->getSize().y / 2), windowSize, worldSize);
	EnemyTargetedMover::Initialize(texture, windowSize, worldSize);
	Enemy::Initialize(shipExplosion);
	Enemy::mRadar->setTexture(*radarTexture);
	EnemyTargetedMover::mMoveSpeed = 2.5f;
	EnemyTargetedMover::mMoveTimer = 6.666f;
	EnemyTargetedMover::mMaxVolicityX = 16.666f;
	EnemyTargetedMover::mMaxVolicityY = 8.666f;

	mNextTargetLocation.height = 8;
	mNextTargetLocation.width = 8;
}

void AngreiferFoundCity::Setup(sf::Vector2f position, sf::Vector2f velocity, int cityNumber, sf::Vector2f cityPosition)
{
	EnemyRandomShooter::SetActive(true);
	EnemyTargetedMover::Setup(position, velocity);
	mTargetCity = cityPosition;
	mNextTargetPosition = position;
	mNextTargetPosition = NextTarget();
	mBombCityNumber = cityNumber;
}

void AngreiferFoundCity::PlayerPointer(std::shared_ptr<Player> playerSP)
{	
	Enemy::pPlayer = playerSP;
	EnemyRandomShooter::PlayerPointer(playerSP);
}

void AngreiferFoundCity::CityPointer(std::shared_ptr<Cities> citySP)
{
	pCities = citySP;
}

int AngreiferFoundCity::GetCityNumber(void)
{
	return mBombCityNumber;
}

sf::Vector2f AngreiferFoundCity::GetCityTarget(void)
{
	return mTargetCity;
}

bool AngreiferFoundCity::InPositionToBombCity(void) //This lets EnemySpaner know this one is ready to bomb so that it can be turned into a city bomber.
{
	if (pCities->CityCollusion(mBombCityNumber).intersects(*Entity::GetCollision()))
	{
		return true;
	}

	return false;
}

AngreiferFoundCity::AngreiferFoundCity(void)
{
}

sf::Vector2f AngreiferFoundCity::NextTarget(void)
{
	sf::Vector2f nextPosition;

	nextPosition.x = mTargetCity.x + EnemyTargetedMover::RandomNumber(0.0f, mTargetCity.x - mNextTargetPosition.x);
	nextPosition.y = mTargetCity.y - EnemyTargetedMover::RandomNumber(0.0f, mTargetCity.y - mNextTargetPosition.y);

	mNextTargetLocation.left = nextPosition.x - 4.0f;
	mNextTargetLocation.top = nextPosition.y - 4.0f;

	return sf::Vector2f(nextPosition.x, nextPosition.y);
}