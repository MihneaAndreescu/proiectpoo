#pragma once

#include <SFML/Graphics.hpp>
#include "ObjectUpdateInfo.h"

class GameObject : public sf::Drawable {
public:
	virtual void update(ObjectUpdateInfo info) = 0;
};