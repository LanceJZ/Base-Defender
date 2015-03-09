#include "Angriff_auf_Stadt.h"

void Angriff_auf_Stadt::Update(sf::Time *delta)
{
	if (Entity::m_Active)
	{
		if (EnemyTargetedMover::DoesMovementChange())
			EnemyTargetedMover::ChaseTarget(&mNextTargetPosition);

		if (mBombDropTimer < Entity::mClock.getElapsedTime().asSeconds())
		{
			mBombDropTimer = EnemyTargetedMover::ResetTimer(mBombDropAmount, mBombDropAmount / 2);
			DropBomb();
		}
	}

	EnemyRandomShooter::SetActive(Entity::m_Active);
	EnemyRandomShooter::Update(delta, Entity::GetPosition());
	EnemyTargetedMover::Update(delta);
	mBomb->Update(delta);
}

void Angriff_auf_Stadt::Draw(sf::RenderWindow *window)
{
	mBomb->Draw(window);
	EnemyRandomShooter::Draw(window);
	Enemy::Draw(window);
}

void Angriff_auf_Stadt::DrawOtherSide(sf::RenderWindow *window)
{
	mBomb->DrawOtherSide(window);
	EnemyRandomShooter::DrawOtherSide(window);
	Enemy::DrawOtherSide(window);
}

void Angriff_auf_Stadt::Initialize(sf::Texture *texture, sf::Texture *radarTexture, sf::Texture *shotTexture, sf::Texture *bombTexture, sf::Texture *bombExplosion, sf::Texture *shipExplosion,
	sf::Vector2u windowSize, sf::Vector2f worldSize)
{
	mBombTexture = bombTexture;
	EnemyRandomShooter::Initialize(shotTexture, sf::Vector2i(texture->getSize().x / 2, texture->getSize().y / 2), windowSize, worldSize);
	EnemyTargetedMover::Initialize(texture, windowSize, worldSize);
	Enemy::Initialize(shipExplosion);
	Enemy::mRadar->setTexture(*radarTexture);
	mBomb->Initialize(bombTexture, bombExplosion, windowSize, worldSize);
	EnemyTargetedMover::mMoveSpeed = 1.666f;
	EnemyTargetedMover::mMoveTimer = 6.666f;
	EnemyTargetedMover::mMaxVolicityX = 6.666f;
	EnemyTargetedMover::mMaxVolicityY = 1.666f;

	mBombDropAmount = 30.0f;
}

void Angriff_auf_Stadt::Setup(sf::Vector2f position, sf::Vector2f velocity, int cityNumber, sf::Vector2f cityPosition)
{
	EnemyRandomShooter::SetActive(true);
	EnemyTargetedMover::Setup(position, velocity);
	mBombCityNumber = cityNumber;
	mNextTargetPosition = sf::Vector2f(cityPosition.x, cityPosition.y - 100);
	mTargetCity = sf::Vector2f(pCities->CityCollusion(cityNumber).left + pCities->CityCollusion(cityNumber).width / 2, 
		pCities->CityCollusion(cityNumber).top + pCities->CityCollusion(cityNumber).height / 2);
	mBombDropTimer = EnemyTargetedMover::ResetTimer(mBombDropAmount, mBombDropAmount / 2);
	sf::Vector2f targetCity = sf::Vector2f(pCities->CityCollusion(mBombCityNumber).left,
		pCities->CityCollusion(mBombCityNumber).top);
	mBomb->CityInfo(targetCity, pCities->CityCollusion(mBombCityNumber).width, cityNumber);
	mBomb->CityPointer(pCities);
}

void Angriff_auf_Stadt::PlayerPointer(std::shared_ptr<Player> playerSP)
{
	Enemy::pPlayer = playerSP;
	EnemyRandomShooter::PlayerPointer(playerSP);
}

void Angriff_auf_Stadt::CityPointer(std::shared_ptr<Cities> citySP)
{
	pCities = citySP;
}

bool Angriff_auf_Stadt::GetCityDistroyed(void)
{
	return pCities->GetCityDistroyed(mBombCityNumber);
}

Angriff_auf_Stadt::Angriff_auf_Stadt(void)
{
	mBomb = new EnemyCityBomb();
}

void Angriff_auf_Stadt::DropBomb(void)
{
	mBomb->DropBomb(sf::Vector2f(Entity::GetPosition()->x + Entity::GetCollision()->width / 2, Entity::GetPosition()->y + Entity::GetCollision()->height));
}