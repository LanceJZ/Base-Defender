#include "Common.h"

sf::Vector2f Common::AngleToVector(float angle, float magnitude)
{
	sf::Vector2f vector;

	vector.y = std::sinf(angle) * magnitude;
	vector.x = std::cosf(angle) * magnitude;

	return vector;
}

float Common::AngleToTarget(sf::Vector2f origin, sf::Vector2f target)
{
	return std::atan2f(target.y - origin.y, target.x - origin.x);
}

float Common::ResetTimer(float Amount, float maxAmount, float minAmount)
{
	return mClock.getElapsedTime().asSeconds() + float(rand() & int(maxAmount - minAmount)) + minAmount;
}

Common::Common()
{
}