#include "SpaceShip.h"
#include "Math.h"
#include <cmath>

void SpaceShip::prepDrawSpaceShipMainBodyVertexArray() {
    m_drawInfo.spaceShipMainBodyVertexArray.clear();
    m_drawInfo.spaceShipMainBodyVertexArray.setPrimitiveType(sf::Quads);
    m_drawInfo.spaceShipMainBodyVertexArray.append(sf::Vertex{ {m_center.x - m_size.x * 0.5f, m_center.y - m_size.y * 0.5f} });
    m_drawInfo.spaceShipMainBodyVertexArray.append(sf::Vertex{ {m_center.x - m_size.x * 0.5f, m_center.y + m_size.y * 0.5f} });
    m_drawInfo.spaceShipMainBodyVertexArray.append(sf::Vertex{ {m_center.x + m_size.x * 0.5f, m_center.y + m_size.y * 0.5f} });
    m_drawInfo.spaceShipMainBodyVertexArray.append(sf::Vertex{ {m_center.x + m_size.x * 0.5f, m_center.y - m_size.y * 0.5f} });
    m_drawInfo.spaceShipMainBodyVertexArray[0].color = m_drawInfo.spaceShipMainBodyVertexArray[3].color = sf::Color::Red;
    m_drawInfo.spaceShipMainBodyVertexArray[1].color = m_drawInfo.spaceShipMainBodyVertexArray[2].color = sf::Color::Green;

    m_innerRectangleShape.setSize(m_size);

    m_innerRectangleShape.setPosition(m_center.x - m_size.x * 0.5f, m_center.y - m_size.y * 0.5f);
}

void SpaceShip::prepDrawLeftRocket() {
    float length = Math::norm(m_drawInfo.spaceShipMainBodyVertexArray[3].position - m_drawInfo.spaceShipMainBodyVertexArray[0].position);
    sf::Vector2f backMidPoint = (m_drawInfo.spaceShipMainBodyVertexArray[1].position + m_drawInfo.spaceShipMainBodyVertexArray[2].position) * 0.5f;
    m_drawInfo.leftRocketVertexArray.clear();
    m_drawInfo.leftRocketVertexArray.setPrimitiveType(sf::Triangles);
    m_drawInfo.leftRocketVertexArray.append(sf::Vertex{ m_drawInfo.spaceShipMainBodyVertexArray[1].position });
    m_drawInfo.leftRocketVertexArray.append(sf::Vertex{ {m_drawInfo.spaceShipMainBodyVertexArray[1].position.x + length * 0.25f, m_drawInfo.spaceShipMainBodyVertexArray[1].position.y + length * 0.5f} });
    m_drawInfo.leftRocketVertexArray.append(sf::Vertex{ backMidPoint });
    m_drawInfo.leftRocketVertexArray[0].color = m_drawInfo.leftRocketVertexArray[1].color = m_drawInfo.leftRocketVertexArray[2].color = sf::Color::Green;
}

void SpaceShip::prepDrawRightRocket() {
    float length = Math::norm(m_drawInfo.spaceShipMainBodyVertexArray[3].position - m_drawInfo.spaceShipMainBodyVertexArray[0].position);
    sf::Vector2f backMidPoint = (m_drawInfo.spaceShipMainBodyVertexArray[1].position + m_drawInfo.spaceShipMainBodyVertexArray[2].position) * 0.5f;
    m_drawInfo.rightRocketVertexArray.clear();
    m_drawInfo.rightRocketVertexArray.setPrimitiveType(sf::Triangles);
    m_drawInfo.rightRocketVertexArray.append(sf::Vertex{ m_drawInfo.spaceShipMainBodyVertexArray[2].position });
    m_drawInfo.rightRocketVertexArray.append(sf::Vertex{ {m_drawInfo.spaceShipMainBodyVertexArray[2].position.x - length * 0.25f, m_drawInfo.spaceShipMainBodyVertexArray[1].position.y + length * 0.5f} });
    m_drawInfo.rightRocketVertexArray.append(sf::Vertex{ backMidPoint });
    m_drawInfo.rightRocketVertexArray[0].color = m_drawInfo.rightRocketVertexArray[1].color = m_drawInfo.rightRocketVertexArray[2].color = sf::Color::Green;
}

void SpaceShip::prepDrawRockets() {
    prepDrawLeftRocket();
    prepDrawRightRocket();
}

void SpaceShip::prepDrawCockpit() {
    sf::Vector2f frontMidPoint = (m_drawInfo.spaceShipMainBodyVertexArray[0].position + m_drawInfo.spaceShipMainBodyVertexArray[3].position) * 0.5f;
    float length = Math::norm(m_drawInfo.spaceShipMainBodyVertexArray[3].position - m_drawInfo.spaceShipMainBodyVertexArray[0].position);
    m_drawInfo.cockPitCircleShape.setPosition(frontMidPoint);
    m_drawInfo.cockPitCircleShape.setRadius(length * 0.5f);
    m_drawInfo.cockPitCircleShape.setOrigin(m_drawInfo.cockPitCircleShape.getRadius() * sf::Vector2f(1, 1));
    m_drawInfo.cockPitCircleShape.setFillColor(sf::Color::Red);
}

void SpaceShip::prepDrawGasCircles() {
    float length = Math::norm(m_drawInfo.spaceShipMainBodyVertexArray[3].position - m_drawInfo.spaceShipMainBodyVertexArray[0].position);
    m_drawInfo.gasCircleShapes.clear();
    if (m_movingForward) {
        prepDrawAddGasCircle(m_drawInfo.leftRocketVertexArray[1].position, length);
        prepDrawAddGasCircle(m_drawInfo.rightRocketVertexArray[1].position, length);
    }
    if (m_movingClockwise) {
        prepDrawAddGasCircle(m_drawInfo.leftRocketVertexArray[0].position, length);
    }
    if (m_movingCounterClockwise) {
        prepDrawAddGasCircle(m_drawInfo.rightRocketVertexArray[0].position, length);
    }
}

void SpaceShip::prepDrawAddGasCircle(const sf::Vector2f& position, float length) {
    sf::CircleShape circle;
    circle.setPosition(position);
    circle.setRadius(length * 0.1f);
    circle.setOrigin(circle.getRadius() * sf::Vector2f(1, 1));
    circle.setFillColor(sf::Color::Yellow);
    m_drawInfo.gasCircleShapes.push_back(circle);
}

sf::RectangleShape rotateAroundPoint(sf::RectangleShape shape, const sf::Vector2f& origin, float angle) {
    sf::Vector2f pos = shape.getPosition();
    sf::Vector2f newPos = Math::rotateAroundPoint(origin, pos, angle);
    shape.setPosition(newPos);
    shape.rotate(angle / Math::PI * 180);
    return shape;
}

void SpaceShip::prepDrawApplyRotation() {
    for (int i = 0; i < 4; i++) {
        m_drawInfo.spaceShipMainBodyVertexArray[i].position = Math::rotateAroundPoint(m_center, m_drawInfo.spaceShipMainBodyVertexArray[i].position, m_angle);
    }
    for (int i = 0; i < 3; i++) {
        m_drawInfo.leftRocketVertexArray[i].position = Math::rotateAroundPoint(m_center, m_drawInfo.leftRocketVertexArray[i].position, m_angle);
        m_drawInfo.rightRocketVertexArray[i].position = Math::rotateAroundPoint(m_center, m_drawInfo.rightRocketVertexArray[i].position, m_angle);
    }
    m_drawInfo.cockPitCircleShape.setPosition(Math::rotateAroundPoint(m_center, m_drawInfo.cockPitCircleShape.getPosition(), m_angle));
    for (auto& circleShape : m_drawInfo.gasCircleShapes) {
        circleShape.setPosition(Math::rotateAroundPoint(m_center, circleShape.getPosition(), m_angle));
    }
}

void SpaceShip::prepDraw() {
    prepDrawSpaceShipMainBodyVertexArray();
    prepDrawRockets();
    prepDrawCockpit();
    prepDrawGasCircles();
    prepDrawApplyRotation();
    if (m_invinc >= 0) {
        sf::Color color = sf::Color(0, 0, 255, (cos(m_invinc * 10) + 1) / 2 * 255);
        m_drawInfo.cockPitCircleShape.setFillColor(color);
        for (auto& circleShape : m_drawInfo.gasCircleShapes) {
            circleShape.setFillColor(color);
        }
        for (size_t i = 0; i < m_drawInfo.leftRocketVertexArray.getVertexCount(); i++) {
            m_drawInfo.leftRocketVertexArray[i].color = color;
        }
        for (size_t i = 0; i < m_drawInfo.rightRocketVertexArray.getVertexCount(); i++) {
            m_drawInfo.rightRocketVertexArray[i].color = color;
        }
        for (size_t i = 0; i < m_drawInfo.spaceShipMainBodyVertexArray.getVertexCount(); i++) {
            m_drawInfo.spaceShipMainBodyVertexArray[i].color = color;
        }
    }
}

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
    m_elapsedCounterClockwise(0),
    m_invinc(0),
    m_hearts(5) {
}

SpaceShip::SpaceShip(const SpaceShip& other) :
    m_name(other.m_name),
    m_center(other.m_center),
    m_size(other.m_size),
    m_speed(other.m_speed),
    m_angle(other.m_angle),
    m_elapsedClockwise(other.m_elapsedClockwise),
    m_elapsedCounterClockwise(other.m_elapsedCounterClockwise),
    m_drawInfo(other.m_drawInfo),
    m_invinc(other.m_invinc),
    m_hearts(other.m_hearts) {
}

/*
    float m_invinc;
    int m_hearts;
*/

SpaceShip SpaceShip::operator = (const SpaceShip& other) {
    if (this != &other) {
        this->m_name = other.m_name;
        this->m_size = other.m_size;
        this->m_center = other.m_center;
        this->m_speed = other.m_speed;
        this->m_angle = other.m_angle;
        this->m_elapsedClockwise = other.m_elapsedClockwise;
        this->m_elapsedCounterClockwise = other.m_elapsedCounterClockwise;
        this->m_drawInfo = other.m_drawInfo;
        this->m_invinc = other.m_invinc;
        this->m_hearts = other.m_hearts;
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

void SpaceShip::invincible(double tInvinc) {
    m_hearts--;
    m_invinc = tInvinc;
}

void SpaceShip::resetMovementFlags() {
    m_movingForward = false;
    m_movingClockwise = false;
    m_movingCounterClockwise = false;
}

sf::Vector2f SpaceShip::computeDirection(const sf::Vector2f& mousePosition, const sf::Vector2f& center) {
    return Math::normalize(mousePosition - center);
}

void SpaceShip::updateAngle(const sf::Vector2f& direction) {
    m_angle = atan2(direction.y, direction.x) + Math::PI / 2;
}

void SpaceShip::updateMovementFlags() {
    m_movingForward = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

sf::Vector2f SpaceShip::calculateDelta(const sf::Vector2f& direction, const sf::Vector2f& perpDirection) {
    sf::Vector2f delta(0, 0);
    delta += direction * (float)(m_movingForward);
    delta += -perpDirection * (float)(m_movingClockwise);
    delta += perpDirection * (float)(m_movingCounterClockwise);
    return delta;
}

void SpaceShip::applyMovement(sf::Vector2f& delta, float deltaTime) {
    if (Math::norm(delta) > 1e-10) {
        delta = Math::normalize(delta) * m_speed;
        m_center += delta * deltaTime;
    }
}

void SpaceShip::updateRotationTimers(float directionCross, float deltaTime) {
    if (directionCross > 0) {
        m_elapsedClockwise = 0;
    }
    else {
        m_elapsedClockwise += deltaTime;
    }
    if (-directionCross > 0) {
        m_elapsedCounterClockwise = 0;
    }
    else {
        m_elapsedCounterClockwise += deltaTime;
    }
}

void SpaceShip::adjustSimultaneousRotation() {
    const float Time = 0.2f;
    m_movingClockwise = (m_elapsedClockwise <= Time);
    m_movingCounterClockwise = (m_elapsedCounterClockwise <= Time);
    if (m_movingClockwise && m_movingCounterClockwise) {
        m_movingClockwise = m_movingCounterClockwise = false;
    }
}

void SpaceShip::update(ObjectUpdateInfo drawInfo) {
    m_invinc -= drawInfo.deltaTime;
    resetMovementFlags();
    sf::Vector2f direction = computeDirection(drawInfo.mousePosition, m_center);
    updateAngle(direction);
    updateMovementFlags();
    sf::Vector2f perpDirection = Math::perp(direction);
    sf::Vector2f delta = calculateDelta(direction, perpDirection);
    applyMovement(delta, drawInfo.deltaTime);
    float directionCross = Math::cross(direction, m_lastDirection);
    updateRotationTimers(directionCross, drawInfo.deltaTime);
    adjustSimultaneousRotation();
    m_lastDirection = direction;
}

sf::RectangleShape SpaceShip::getRigidBodyBoundingBox(int tag) {
    if (m_invinc >= 0 && tag == 0) {
        sf::RectangleShape shape;
        shape.setPosition(sf::Vector2f(1, 1) * (float)(1e9));
        shape.setSize(sf::Vector2f(0, 0));
        return shape;
    }
    auto increasedRectangle = m_innerRectangleShape;
    increasedRectangle.setSize(sf::Vector2f(increasedRectangle.getSize().x, increasedRectangle.getSize().y * 1.5f));
    increasedRectangle.setPosition(increasedRectangle.getPosition() + sf::Vector2f(0, -increasedRectangle.getSize().y * 0.17f));
    auto rotatedIncreasedRectangle = rotateAroundPoint(increasedRectangle, m_center, m_angle);
    return rotatedIncreasedRectangle;
}

std::ostream& operator << (std::ostream& os, const SpaceShip& spaceShip) {
    os << "(name = " << spaceShip.m_name << ")";
    return os;
}

int SpaceShip::countHearts() {
    return m_hearts;
}

int SpaceShip::countShrooms() {
    return m_shrooms;
}

void SpaceShip::increase() {
    m_shrooms++;
}

float SpaceShip::getMass() const {
    if (m_invinc >= 0) {
        return -100;
    }
    return 0;
}

void SpaceShip::clearForces() {

}

void SpaceShip::applyForce(sf::Vector2f force) {

}