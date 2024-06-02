#pragma once

#include <SFML/Graphics.hpp>
#include "DuneException.h"

class Heart : public sf::Drawable {
private:
    sf::CircleShape m_topLeftCircleShape;
    sf::CircleShape m_topRightCircleShape;
    sf::ConvexShape m_bottomPartOfHeart;
public:
    void reConstruct(float x, float y, float newSize);
    Heart(float x, float y, float size);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};