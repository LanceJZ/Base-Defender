#include "EnemyRandomMover.h"

void EnemyRandomMover::Update(sf::Time *delta)
{
	Entity::Update(delta);

	if (m_Active)
	{
		Enemy::CheckVelocity();

		Enemy::HitbyPlayerShot();

		if (DoesMovementChange())
			ChangeMovement();
	}
}

void EnemyRandomMover::Initialize(sf::Texture *texture, sf::Vector2u windowSize, sf::Vector2f worldSize)
{
	mMoveSpeed = 2.5f;
	mMoveTimer = 10.5f;
	mNextMoveTime = MoveTime();
	Entity::Initialize(texture, windowSize, worldSize);
}

void EnemyRandomMover::Setup(sf::Vector2f position, sf::Vector2f velocity)
{
	Entity::SetPosition(&position);
	m_Velocity = velocity;
	m_Active = true;	
}

//sf::Vector2f *EnemyRandomMover::GetPosition(void)
//{
//	return Entity::GetPosition();
//}
//
//sf::FloatRect EnemyRandomMover::GetCollusion(void)
//{
//	return m_Collusion;
//}
//
//bool EnemyRandomMover::HitbyPlayerShot(void)
//{
//	return Enemy::HitbyPlayerShot();
//}

EnemyRandomMover::EnemyRandomMover(void)
{
}

float EnemyRandomMover::MoveTime(void)
{
	return mClock.getElapsedTime().asSeconds() + float(rand() % int(mMoveTimer) + int(mMoveTimer / 3));
}

void EnemyRandomMover::ChangeMovement(void)
{
	float magnitude = float((rand() % int(mMoveSpeed / 2)) + int(mMoveSpeed / 2));
	float random = rand() / (RAND_MAX + 1.0f);
	float angle = random * 2.0f * (float)M_PI;

	Entity::m_Acceleration.x = cos(angle) * magnitude;
	Entity::m_Acceleration.y = sin(angle) * magnitude;
}

bool EnemyRandomMover::DoesMovementChange(void)
{
	if (mNextMoveTime < mClock.getElapsedTime().asSeconds())
	{
		mNextMoveTime = MoveTime();
		return true;
	}

	return false;
}