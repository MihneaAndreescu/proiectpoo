#pragma once

#include <SFML/Graphics.hpp>

struct ObjectUpdateInfo {
	const float dt;
	const sf::Vector2f mousePosition;
	ObjectUpdateInfo(const float dt, const sf::Vector2f mousePosition);
};