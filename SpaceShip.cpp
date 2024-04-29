#include "SpaceShip.h"
#include "Math.h"
#include <cmath>


SpaceShip::SpaceShip(const std::string& name, const sf::Vector2f& center, const sf::Vector2f size, float speed) :
    m_name(name),
    m_center(center),
    m_size(size),
    m_speed(speed),
    m_angle(0),
    m_movingForward(false),
    m_movingClockwise(false),
    m_movingCounterClockwise(false),
    m_elapsedClockwise(0),
    m_elapsedCounterClockwise(0) {
}

SpaceShip::SpaceShip(const SpaceShip& other) :
    m_name(other.m_name),
    m_center(other.m_center),
    m_size(other.m_size),
    m_speed(other.m_speed),
    m_angle(other.m_angle),
    m_elapsedClockwise(other.m_elapsedClockwise),
    m_elapsedCounterClockwise(other.m_elapsedCounterClockwise) {
}

SpaceShip SpaceShip::operator = (const SpaceShip& other) {
    if (this != &other) {
        this->m_name = other.m_name;
        this->m_size = other.m_size;
        this->m_center = other.m_center;
        this->m_speed = other.m_speed;
        this->m_angle = other.m_angle;
        this->m_elapsedClockwise = other.m_elapsedClockwise;
        this->m_elapsedCounterClockwise = other.m_elapsedCounterClockwise;
    }
    return *this;
}

sf::Vector2f SpaceShip::getCenter() const {
    return m_center;
}

SpaceShip::~SpaceShip() {

}

void SpaceShip::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const {
    renderTarget.draw(m_drawInfo.cockPitCircleShape, renderStates);
    renderTarget.draw(m_drawInfo.leftRocketVertexArray, renderStates);
    renderTarget.draw(m_drawInfo.rightRocketVertexArray, renderStates);
    renderTarget.draw(m_drawInfo.spaceShipMainBodyVertexArray, renderStates);
    for (auto& circleShape : m_drawInfo.gasCircleShapes) {
        renderTarget.draw(circleShape, renderStates);
    }
}

float cross(sf::Vector2f a, sf::Vector2f b) {
    return a.x * b.y - a.y * b.x;
}

void SpaceShip::update(ObjectUpdateInfo m_drawInfo) {
    m_movingForward = false;
    m_movingClockwise = false;
    m_movingCounterClockwise = false;
    sf::Vector2f direction = Math::normalize(m_drawInfo.mousePosition - m_center);
    m_angle = atan2(direction.y, direction.x) + Math::PI / 2;
    sf::Vector2f perpDirection = Math::perp(direction);
    sf::Vector2f delta = sf::Vector2f(0, 0);
    m_movingForward = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    m_movingClockwise = false;
    m_movingCounterClockwise = false;
    delta += direction * (float)(m_movingForward);
    delta += -perpDirection * (float)(m_movingClockwise);
    delta += perpDirection * (float)(m_movingCounterClockwise);
    if (Math::norm(delta) > 1e-10) {
        delta = Math::normalize(delta) * m_speed;
        m_center += delta * m_drawInfo.dt;
    }
    float directionCross = cross(direction, m_lastDirection);
    if (directionCross > 0) {
        m_elapsedClockwise = 0;
    }
    else {
        m_elapsedClockwise += m_drawInfo.dt;
    }
    if (directionCross < 0) {
        m_elapsedCounterClockwise = 0;
    }
    else {
        m_elapsedCounterClockwise += m_drawInfo.dt;
    }
    const float Time = 0.2f;
    m_movingClockwise = (m_elapsedClockwise <= Time);
    m_movingCounterClockwise = (m_elapsedCounterClockwise <= Time);
    if (m_movingClockwise && m_movingCounterClockwise) {
        m_movingClockwise = m_movingCounterClockwise = false;
    }
    m_lastDirection = direction;
}

std::ostream& operator << (std::ostream& os, const SpaceShip& spaceShip) {
    os << "(name = " << spaceShip.m_name << ")";
    return os;
}
