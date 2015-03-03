#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>

class Common
{
public:
	Common();

	float AngleToTarget(sf::Vector2f origin, sf::Vector2f target); //Returns angle from origin to target.
	float ResetTimer(float Amount, float maxAmount, float minAmount);
	sf::Vector2f AngleToVector(float angle, float magnitude); //Takes angle magnitude and turns it into vector of velocity.
	sf::Clock mClock;
};

