#include "EnemyRandomMover.h"

void EnemyRandomMover::Update(sf::Time *delta)
{
	Enemy::Update(delta);

	if (m_Active)
	{
		Enemy::CheckVelocity();

		if (DoesMovementChange())
			ChangeMovement();
	}
}

void EnemyRandomMover::Initialize(sf::Texture *texture, sf::Vector2u windowSize, sf::Vector2f worldSize)
{
	Entity::Initialize(texture, windowSize, worldSize);
	mMoveSpeed = 2.5f;
	mMoveTimer = 45.5f;
	mNextMoveTime = Common::ResetTimer(mMoveTimer / 4, mMoveTimer / 8);
}

void EnemyRandomMover::Setup(sf::Vector2f position, sf::Vector2f velocity)
{
	Entity::SetPosition(&position);
	Entity::m_Velocity = velocity;
	Entity::m_Active = true;
}

EnemyRandomMover::EnemyRandomMover(void)
{
}

void EnemyRandomMover::ChangeMovement(void)
{
	float magnitude = Common::RandomNumber(mMoveSpeed / 16, mMoveSpeed);
	float angle = Common::RandomNumber(0.0f, 2.0f * (float)M_PI);

	Entity::m_Acceleration.x = cos(angle) * magnitude;
	Entity::m_Acceleration.y = sin(angle) * magnitude;
}

bool EnemyRandomMover::DoesMovementChange(void)
{
	if (mNextMoveTime < mClock.getElapsedTime().asSeconds())
	{
		mNextMoveTime = Common::ResetTimer(mMoveTimer, mMoveTimer / 4);
		return true;
	}

	return false;
}