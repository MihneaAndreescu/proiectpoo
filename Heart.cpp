#include "Heart.h"

void Heart::reConstruct(float x, float y, float size) {
    float radius = size / 4;
    float adjustedRadius = radius;
    m_topLeftCircleShape.setRadius(adjustedRadius);
    m_topLeftCircleShape.setFillColor(sf::Color::Red);
    m_topLeftCircleShape.setPosition(x - adjustedRadius * 0.8, y);
    m_topLeftCircleShape.setOrigin(sf::Vector2f(1, 1) * adjustedRadius);
    m_topRightCircleShape.setRadius(adjustedRadius);
    m_topRightCircleShape.setFillColor(sf::Color::Red);
    m_topRightCircleShape.setPosition(x + adjustedRadius * 0.8, y);
    m_topRightCircleShape.setOrigin(sf::Vector2f(1, 1) * adjustedRadius);
    m_bottomPartOfHeart.setPointCount(3);
    m_bottomPartOfHeart.setFillColor(sf::Color::Red);
    m_bottomPartOfHeart.setPoint(0, sf::Vector2f(x - 2 * radius * 0.8, y));
    m_bottomPartOfHeart.setPoint(1, sf::Vector2f(x + 2 * radius * 0.8, y));
    m_bottomPartOfHeart.setPoint(2, sf::Vector2f(x, y - radius * 2));
}

Heart::Heart(float x, float y, float size) {
    if (size < 0) {
        throw HeartInitializationException("dimensiune negativa");
    }
    float radius = size / 4;
    float adjustedRadius = radius;
    m_topLeftCircleShape.setRadius(adjustedRadius);
    m_topLeftCircleShape.setFillColor(sf::Color::Red);
    m_topLeftCircleShape.setPosition(x - adjustedRadius * 0.8, y);
    m_topLeftCircleShape.setOrigin(sf::Vector2f(1, 1) * adjustedRadius);
    m_topRightCircleShape.setRadius(adjustedRadius);
    m_topRightCircleShape.setFillColor(sf::Color::Red);
    m_topRightCircleShape.setPosition(x + adjustedRadius * 0.8, y);
    m_topRightCircleShape.setOrigin(sf::Vector2f(1, 1) * adjustedRadius);
    m_bottomPartOfHeart.setPointCount(3);
    m_bottomPartOfHeart.setFillColor(sf::Color::Red);
    m_bottomPartOfHeart.setPoint(0, sf::Vector2f(x - 2 * radius * 0.8, y));
    m_bottomPartOfHeart.setPoint(1, sf::Vector2f(x + 2 * radius * 0.8, y));
    m_bottomPartOfHeart.setPoint(2, sf::Vector2f(x, y - radius * 2));
}

void Heart::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_topLeftCircleShape, states);
    target.draw(m_topRightCircleShape, states);
    target.draw(m_bottomPartOfHeart, states);
}
