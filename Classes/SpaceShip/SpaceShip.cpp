#include "SpaceShip.h"
#include "../../Math/Math.h"
#include <cmath>



sf::Keyboard::Key m_keyUp;
sf::Keyboard::Key m_keyDown;
sf::Keyboard::Key m_keyLeft;
sf::Keyboard::Key m_keyRight;


SpaceShip::SpaceShip(const std::string& name, const sf::Vector2f& center, const sf::Vector2f size, float speed) :
    m_name(name),
    m_center(center),
    m_size(size),
    m_speed(speed),
    m_angle(0)
{
}

SpaceShip::SpaceShip(const SpaceShip& other) :
    m_name(other.m_name),
    m_center(other.m_center),
    m_size(other.m_size),
    m_speed(other.m_speed),
    m_angle(other.m_angle),
    m_keyUp(other.m_keyUp),
    m_keyDown(other.m_keyDown),
    m_keyLeft(other.m_keyLeft),
    m_keyRight(other.m_keyRight)
{
}

SpaceShip SpaceShip::operator = (const SpaceShip& other)
{
    if (this != &other)
    {
        this->m_name = other.m_name;
        this->m_size = other.m_size;
        this->m_center = other.m_center;
        this->m_speed = other.m_speed;
        this->m_angle = other.m_angle;
        this->m_keyUp = other.m_keyUp;
        this->m_keyDown = other.m_keyDown;
        this->m_keyLeft = other.m_keyLeft;
        this->m_keyRight = other.m_keyRight;
    }
    return *this;
}


sf::Vector2f SpaceShip::getCenter() const
{
    return m_center;
}

sf::Vector2f SpaceShip::getSize() const
{
    return m_size;
}

SpaceShip::~SpaceShip()
{

}

void SpaceShip::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const
{
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

    if (sf::Keyboard::isKeyPressed(m_keyUp))
    {
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

    if (sf::Keyboard::isKeyPressed(m_keyDown))
    {
        sf::CircleShape y;
        y.setPosition(sf::Vector2{ cockPitCircleShape.getPosition().x,  cockPitCircleShape.getPosition().y - cockPitCircleShape.getRadius() });
        y.setRadius(length * 0.1f);
        y.setOrigin(y.getRadius() * sf::Vector2f(1, 1));
        y.setFillColor(sf::Color::Yellow);

        traceCircleShapes.push_back(y);
    }

    if (sf::Keyboard::isKeyPressed(m_keyLeft))
    {
        sf::CircleShape y;
        y.setPosition(leftRocket[0].position);
        y.setRadius(length * 0.1f);
        y.setOrigin(y.getRadius() * sf::Vector2f(1, 1));
        y.setFillColor(sf::Color::Yellow);
        traceCircleShapes.push_back(y);
    }

    if (sf::Keyboard::isKeyPressed(m_keyRight))
    {
        sf::CircleShape y;
        y.setPosition(rightRocket[0].position);
        y.setRadius(length * 0.1f);
        y.setOrigin(y.getRadius() * sf::Vector2f(1, 1));
        y.setFillColor(sf::Color::Yellow);
        traceCircleShapes.push_back(y);
    }

    for (int i = 0; i < 4; i++)
    {
        spaceShipMainBodyVertexArray[i].position = Math::rotateArountPoint(m_center, spaceShipMainBodyVertexArray[i].position, m_angle);
    }
    for (int i = 0; i < 3; i++)
    {
        leftRocket[i].position = Math::rotateArountPoint(m_center, leftRocket[i].position, m_angle);
        rightRocket[i].position = Math::rotateArountPoint(m_center, rightRocket[i].position, m_angle);
    }
    cockPitCircleShape.setPosition(Math::rotateArountPoint(m_center, cockPitCircleShape.getPosition(), m_angle));
    for (auto& circleShape : traceCircleShapes)
    {
        circleShape.setPosition(Math::rotateArountPoint(m_center, circleShape.getPosition(), m_angle));
    }
    renderTarget.draw(cockPitCircleShape, renderStates);
    renderTarget.draw(leftRocket, renderStates);
    renderTarget.draw(rightRocket, renderStates);
    renderTarget.draw(spaceShipMainBodyVertexArray, renderStates);
    for (auto& circleShape : traceCircleShapes)
    {
        renderTarget.draw(circleShape, renderStates);
    }
}

std::ostream& operator<<(std::ostream& os, const SpaceShip& spaceShip)
{
    os << "(name = " << spaceShip.m_name << ")";
    return os;
}

void SpaceShip::update(float dt, sf::Vector2f mousePosition)
{
    sf::Vector2f direction = Math::normalize(mousePosition - m_center);
    m_angle = atan2(direction.y, direction.x) + Math::PI / 2;
    sf::Vector2f perpDirection = Math::perp(direction);

    sf::Vector2f delta = sf::Vector2f(0, 0);
    if (sf::Keyboard::isKeyPressed(m_keyUp))
    {
        delta += direction;
    }
    if (sf::Keyboard::isKeyPressed(m_keyDown))
    {
        delta -= direction;
    }
    if (sf::Keyboard::isKeyPressed(m_keyLeft))
    {
        delta -= perpDirection;
    }
    if (sf::Keyboard::isKeyPressed(m_keyRight))
    {
        delta += perpDirection;
    }
    if (Math::norm(delta) > 1e-10)
    {
        delta = Math::normalize(delta) * m_speed;
        m_center += delta * dt;
    }
}

void SpaceShip::setKeyboardKeyForUp(sf::Keyboard::Key key)
{
    m_keyUp = key;
}

void SpaceShip::setKeyboardKeyForDown(sf::Keyboard::Key key)
{
    m_keyDown = key;
}

void SpaceShip::setKeyboardKeyForLeft(sf::Keyboard::Key key)
{
    m_keyLeft = key;
}

void SpaceShip::setKeyboardKeyForRight(sf::Keyboard::Key key)
{
    m_keyRight = key;
}