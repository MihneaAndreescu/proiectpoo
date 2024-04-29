#pragma once

#include <SFML/Graphics.hpp>
#include "ObjectUpdateInfo.h"

class GameObject : public sf::Drawable {
public:
	virtual void update(ObjectUpdateInfo m_drawInfo) = 0;
	virtual void prepDraw() = 0;
};