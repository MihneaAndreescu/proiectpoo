#pragma once

#include <SFML/Graphics.hpp>

class GameObject : public sf::Drawable {
public:
	virtual void update(float dt, sf::Vector2f mousePosition) = 0;
};