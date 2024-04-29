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
    sf::VertexArray spaceShipMainBodyVertexArray(sf::Quads);
    spaceShipMainBodyVertexArray.append(sf::Vertex{ { m_center.x - m_size.x * 0.5f, m_center.y - m_size.y * 0.5f } });
    spaceShipMainBodyVertexArray.append(sf::Vertex{ { m_center.x - m_size.x * 0.5f, m_center.y + m_size.y * 0.5f } });
    spaceShipMainBodyVertexArray.append(sf::Vertex{ { m_center.x + m_size.x * 0.5f, m_center.y + m_size.y * 0.5f } });
    spaceShipMainBodyVertexArray.append(sf::Vertex{ { m_center.x + m_size.x * 0.5f, m_center.y - m_size.y * 0.5f } });
    spaceShipMainBodyVertexArray[0].color = spaceShipMainBodyVertexArray[3].color = sf::Color::Red;
    spaceShipMainBodyVertexArray[1].color = spaceShipMainBodyVertexArray[2].color = sf::Color::Green;

    sf::Vector2f frontMidPoint = (spaceShipMainBodyVertexArray[0].position + spaceShipMainBodyVertexArray[3].position) * 0.5f;
    sf::Vector2f backMidPoint = (spaceShipMainBodyVertexArray[1].position + spaceShipMainBodyVertexArray[2].position) * 0.5f;
    float length = Math::norm(spaceShipMainBodyVertexArray[3].position - spaceShipMainBodyVertexArray[0].position);

    sf::VertexArray leftRocket(sf::Triangles);

    leftRocket.append(sf::Vertex{ spaceShipMainBodyVertexArray[1].position });
    leftRocket.append(sf::Vertex{ {spaceShipMainBodyVertexArray[1].position.x + length * 0.25f, spaceShipMainBodyVertexArray[1].position.y + length * 0.5f} });
    leftRocket.append(sf::Vertex{ backMidPoint });
    leftRocket[0].color = leftRocket[1].color = leftRocket[2].color = sf::Color::Green;

    sf::VertexArray rightRocket(sf::Triangles);

    rightRocket.append(sf::Vertex{ spaceShipMainBodyVertexArray[2].position });
    rightRocket.append(sf::Vertex{ {spaceShipMainBodyVertexArray[2].position.x - length * 0.25f, spaceShipMainBodyVertexArray[1].position.y + length * 0.5f} });
    rightRocket.append(sf::Vertex{ backMidPoint });
    rightRocket[0].color = rightRocket[1].color = rightRocket[2].color = sf::Color::Green;

    sf::CircleShape cockPitCircleShape;
    cockPitCircleShape.setPosition(frontMidPoint);
    cockPitCircleShape.setRadius(length * 0.5f);
    cockPitCircleShape.setOrigin(cockPitCircleShape.getRadius() * sf::Vector2f(1, 1));
    cockPitCircleShape.setFillColor(sf::Color::Red);
    std::vector<sf::CircleShape> traceCircleShapes;
    if (m_movingForward) {
        sf::CircleShape y;
        y.setPosition(leftRocket[1].position);
        y.setRadius(length * 0.1f);
        y.setOrigin(y.getRadius() * sf::Vector2f(1, 1));
        y.setFillColor(sf::Color::Yellow);
        traceCircleShapes.push_back(y);

        y.setPosition(rightRocket[1].position);
        y.setRadius(length * 0.1f);
        y.setOrigin(y.getRadius() * sf::Vector2f(1, 1));
        y.setFillColor(sf::Color::Yellow);
        traceCircleShapes.push_back(y);
    }
    if (m_movingClockwise) {
        sf::CircleShape y;
        y.setPosition(leftRocket[0].position);
        y.setRadius(length * 0.1f);
        y.setOrigin(y.getRadius() * sf::Vector2f(1, 1));
        y.setFillColor(sf::Color::Yellow);
        traceCircleShapes.push_back(y);
    }
    if (m_movingCounterClockwise) {
        sf::CircleShape y;
        y.setPosition(rightRocket[0].position);
        y.setRadius(length * 0.1f);
        y.setOrigin(y.getRadius() * sf::Vector2f(1, 1));
        y.setFillColor(sf::Color::Yellow);
        traceCircleShapes.push_back(y);
    }
    for (int i = 0; i < 4; i++) {
        spaceShipMainBodyVertexArray[i].position = Math::rotateArountPoint(m_center, spaceShipMainBodyVertexArray[i].position, m_angle);
    }
    for (int i = 0; i < 3; i++) {
        leftRocket[i].position = Math::rotateArountPoint(m_center, leftRocket[i].position, m_angle);
        rightRocket[i].position = Math::rotateArountPoint(m_center, rightRocket[i].position, m_angle);
    }
    cockPitCircleShape.setPosition(Math::rotateArountPoint(m_center, cockPitCircleShape.getPosition(), m_angle));
    for (auto& circleShape : traceCircleShapes) {
        circleShape.setPosition(Math::rotateArountPoint(m_center, circleShape.getPosition(), m_angle));
    }
    renderTarget.draw(cockPitCircleShape, renderStates);
    renderTarget.draw(leftRocket, renderStates);
    renderTarget.draw(rightRocket, renderStates);
    renderTarget.draw(spaceShipMainBodyVertexArray, renderStates);
    for (auto& circleShape : traceCircleShapes) {
        renderTarget.draw(circleShape, renderStates);
    }
}

float cross(sf::Vector2f a, sf::Vector2f b) {
    return a.x * b.y - a.y * b.x;
}

void SpaceShip::update(ObjectUpdateInfo info) {
    m_movingForward = false;
    m_movingClockwise = false;
    m_movingCounterClockwise = false;
    sf::Vector2f direction = Math::normalize(info.mousePosition - m_center);
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
        m_center += delta * info.dt;
    }
    float directionCross = cross(direction, m_lastDirection);
    if (directionCross > 0) {
        m_elapsedClockwise = 0;
    }
    else {
        m_elapsedClockwise += info.dt;
    }
    if (directionCross < 0) {
        m_elapsedCounterClockwise = 0;
    }
    else {
        m_elapsedCounterClockwise += info.dt;
    }
    const float Time = 0.2f;
    m_movingClockwise = (m_elapsedClockwise <= Time);
    m_movingCounterClockwise = (m_elapsedCounterClockwise <= Time);
    if (m_movingClockwise && m_movingCounterClockwise) {
        m_movingClockwise = m_movingCounterClockwise = false;
    }
    m_lastDirection = direction;
}

std::ostream& operator<<(std::ostream& os, const SpaceShip& spaceShip) {
    os << "(name = " << spaceShip.m_name << ")";
    return os;
}
