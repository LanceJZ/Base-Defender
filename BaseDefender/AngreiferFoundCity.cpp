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

	EnemyRandomShooter::SetActiveShot(m_Active);
	EnemyRandomShooter::Update(delta, Entity::GetPosition());
	EnemyTargetedMover::Update(delta);
}

void AngreiferFoundCity::Draw(sf::RenderWindow *window)
{
	Entity::Draw(window);
	EnemyRandomShooter::Draw(window);
}

void AngreiferFoundCity::DrawOtherSide(sf::RenderWindow *window)
{
	Entity::DrawOtherSide(window);
	EnemyRandomShooter::DrawOtherSide(window);
}

void AngreiferFoundCity::Initialize(sf::Texture *texture, sf::Texture *shotTexture, sf::Vector2u windowSize, sf::Vector2f worldSize)
{
	EnemyRandomShooter::Initialize(shotTexture, sf::Vector2i(texture->getSize().x / 2, texture->getSize().y / 2), windowSize, worldSize);
	EnemyTargetedMover::Initialize(texture, windowSize, worldSize);
	EnemyTargetedMover::mMoveSpeed = 2.5f;
	EnemyTargetedMover::mMoveTimer = 6.666f;
	EnemyTargetedMover::mMaxVolicityX = 16.666f;
	EnemyTargetedMover::mMaxVolicityY = 8.666f;

	mNextTargetLocation.height = 8;
	mNextTargetLocation.width = 8;
}

void AngreiferFoundCity::Setup(sf::Vector2f position, sf::Vector2f velocity, int cityNumber, sf::Vector2f cityPosition)
{
	EnemyRandomShooter::SetActiveShot(true);
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

	int targetX = int(mTargetCity.x - mNextTargetPosition.x);
	int targetY = int(mTargetCity.y - mNextTargetPosition.y);

	if (targetX == 0)
		targetX = 1;
	
	if (targetY == 0)
		targetY = 1;

	nextPosition.x = mTargetCity.x + rand() % targetX;
	nextPosition.y = mTargetCity.y - rand() % targetY;

	mNextTargetLocation.left = nextPosition.x - 4.0f;
	mNextTargetLocation.top = nextPosition.y - 4.0f;

	return sf::Vector2f(nextPosition.x, nextPosition.y);
}