#pragma once
#include <SFML/Graphics.hpp>
#include <numbers>

namespace Math {
	const float PI = (float)std::numbers::pi;
	sf::Vector2f rotateAroundOrigin(sf::Vector2f point, float angle);
	sf::Vector2f rotateAroundPoint(sf::Vector2f origin, sf::Vector2f point, float angle);
	float dot(sf::Vector2f a, sf::Vector2f b);
	float cross(sf::Vector2f a, sf::Vector2f b);
	float norm(sf::Vector2f a);
	sf::Vector2f normalize(sf::Vector2f a);
	sf::Vector2f perp(sf::Vector2f a);
	bool intersects(const sf::CircleShape& a, const sf::CircleShape& b);
}