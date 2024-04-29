#pragma once
#include <SFML/Graphics.hpp>
#include <numbers>

namespace Math{
	const float PI = std::numbers::pi;
	sf::Vector2f rotateAroundOrigin(sf::Vector2f point, float angle);
	sf::Vector2f rotateArountPoint(sf::Vector2f origin, sf::Vector2f point, float angle);
	float dot(sf::Vector2f a, sf::Vector2f b);
	float norm(sf::Vector2f a);
	sf::Vector2f normalize(sf::Vector2f a);
	sf::Vector2f perp(sf::Vector2f a);
}