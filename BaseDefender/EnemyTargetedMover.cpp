#include "EnemyTargetedMover.h"

void EnemyTargetedMover::Update(sf::Time *delta)
{
	if (m_Active)
	{
		Entity::Update(delta);
		Enemy::CheckVelocity();
		Enemy::HitbyPlayerShot();
	}
}

void EnemyTargetedMover::Initialize(sf::Texture *texture, sf::Vector2u windowSize, sf::Vector2f worldSize)
{
	mMoveSpeed = 18.5f;
	mMoveTimer = 3.5f;
	mNextMoveTime = MoveTime();
	mMaxVolicityX = 150;
	mMaxVolicityY = 30;

	Entity::Initialize(texture, windowSize, worldSize);
}

void EnemyTargetedMover::Setup(sf::Vector2f position, sf::Vector2f velocity)
{
	Entity::SetPosition(&position);
	Entity::m_Velocity = velocity;
	Entity::m_Active = true;
}

EnemyTargetedMover::EnemyTargetedMover(void)
{
}

float EnemyTargetedMover::MoveTime(void)
{
	return mClock.getElapsedTime().asSeconds() + float(rand() % int(mMoveTimer) + int(mMoveTimer / 3));
}

void EnemyTargetedMover::ChaseTarget(sf::Vector2f *target)
{
	float magnitude = float((rand() % int(mMoveSpeed)) + mMoveSpeed / 6.666f);
	float angle = Entity::AngleToTarget(*Entity::GetPosition(), *target);

	m_Acceleration.y = std::sinf(angle) * magnitude;

	if (Entity::GetPosition()->x - target->x > m_WorldSize.x * 0.5f || target->x - Entity::GetPosition()->x > m_WorldSize.x * 0.5f)
		m_Acceleration.x = (std::cosf(angle) * magnitude) * -1;
	else
		m_Acceleration.x = std::cosf(angle) * magnitude;
}

bool EnemyTargetedMover::DoesMovementChange(void)
{
	if (mNextMoveTime < mClock.getElapsedTime().asSeconds())
	{
		mNextMoveTime = MoveTime();
		return true;
	}

	return false;
}