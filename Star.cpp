#include "Star.h"
#include <cmath>

Star::Star(sf::Vector2f position, float size) : m_size(size), m_position(position) {
    if (size <= 0) {
        throw StarInitializationException("Invalid size");
    }
    setSize(size);  
    setPosition(position);  
}

void Star::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const {
    renderTarget.draw(m_shape, renderStates);
}

void Star::setPosition(sf::Vector2f position) {
    m_position = position;
    setShape();
}

sf::Vector2f Star::getPosition() const {
    return m_position;
}

void Star::setShape() {
    m_shape.setPointCount(POINTS * 2);
    m_shape.setFillColor(m_color);
    for (int i = 0; i < POINTS * 2; ++i) {
        float angle = i * Math::PI / POINTS;
        float radius = m_size;
        if (i % 2) {
            radius *= 0.5f;
        }
        sf::Vector2f point(std::cos(m_angle + angle) * radius, std::sin(m_angle + angle) * radius);
        m_shape.setPoint(i, m_position + point);
    }
}

void Star::setSize(float size) {
    m_size = size;
    setShape();
}

float Star::getSize() const {
    return m_size;
}

void Star::setAngle(float angle) {
    m_angle = angle;
    setShape();
}

float Star::getAngle() const {
    return m_angle;
}

void Star::setColor(const DuneColor<unsigned char>& color) {
    m_color = color;
    m_shape.setFillColor(m_color);
}

DuneColor<unsigned char> Star::getColor() const {
    return m_color;
}
