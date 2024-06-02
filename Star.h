#pragma once

#include <SFML/Graphics.hpp>
#include "DuneException.h"

class Star : public sf::Drawable {
private:
    sf::ConvexShape m_shape;

public:
    Star(float x, float y, float size);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
