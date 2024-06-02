#include "Star.h"
#include "DuneException.h"
#include "Math.h"
#include <cmath>

Star::Star(float x, float y, float size) {
    if (size <= 0) {
        throw StarInitializationException("Invalid size");
    }
    const int points = 10;
    m_shape.setPointCount(points * 2);
    m_shape.setFillColor(sf::Color::Yellow);
    for (int i = 0; i < points * 2; ++i) {
        float angle = i * Math::PI / points;
        float radius = size; 
        if (i % 2 == 0) {
            radius *= 0.5f;
        }
        sf::Vector2f point(std::cos(angle) * radius, std::sin(angle) * radius);
        m_shape.setPoint(i, point + sf::Vector2f(x, y));
    }
}

void Star::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_shape, states);
}
