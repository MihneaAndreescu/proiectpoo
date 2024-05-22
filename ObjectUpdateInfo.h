#pragma once

#include <SFML/Graphics.hpp>

struct ObjectUpdateInfo {
	const float deltaTime;
	const sf::Vector2f mousePosition;
	ObjectUpdateInfo(const float deltaTime, const sf::Vector2f mousePosition);
};