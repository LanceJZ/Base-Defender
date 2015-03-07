#include "Common.h"

float *Common::CheckForEdge(float *positionX, float *edgeX)
{
	float *posX = positionX;

	if (*positionX > *edgeX)
		*posX = 0.0f;

	if (*positionX < 0.0f)
		*posX = *edgeX;

	return posX;
}

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

float Common::ResetTimer(float maxAmount, float minAmount) //Fix this.
{	
	return mClock.getElapsedTime().asSeconds() + RandomNumber(minAmount, maxAmount);
}

float Common::RandomNumber(float min, float max)
{
	return rand() / (RAND_MAX + 1.0f) * (max - min) + min;
}

Common::Common()
{

}