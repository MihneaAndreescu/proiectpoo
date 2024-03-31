#include "SpaceShip.h"
#include "../../Math/Math.h"
#include <cmath>

SpaceShip::SpaceShip(const std::string& name, const sf::Vector2f& center, const sf::Vector2f size, float speed) :
    m_name(name),
    m_center(center),
    m_size(size),
    m_speed(speed),
    m_angle(0),
    m_trash(0),
    m_useNow(false)
{
}

SpaceShip::SpaceShip(const SpaceShip& other) :
    m_name(other.m_name),
    m_size(other.m_size),
    m_center(other.m_center),
    m_speed(other.m_speed),
    m_angle(other.m_angle),
    m_trash(other.m_angle),
    m_useNow(other.m_useNow)
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
        this->m_trash = other.m_trash;
        this->m_useNow = other.m_useNow;
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

    sf::VertexArray l(sf::Triangles);

    l.append(sf::Vertex{ spaceShipMainBodyVertexArray[1].position });
    l.append(sf::Vertex{ {spaceShipMainBodyVertexArray[1].position.x + length * 0.25f, spaceShipMainBodyVertexArray[1].position.y + length * 0.5f} });
    l.append(sf::Vertex{ backMidPoint });
    l[0].color = l[1].color = l[2].color = sf::Color::Green;

    sf::VertexArray r(sf::Triangles);

    r.append(sf::Vertex{ spaceShipMainBodyVertexArray[2].position });
    r.append(sf::Vertex{ {spaceShipMainBodyVertexArray[2].position.x - length * 0.25f, spaceShipMainBodyVertexArray[1].position.y + length * 0.5f} });
    r.append(sf::Vertex{ backMidPoint });
    r[0].color = r[1].color = r[2].color = sf::Color::Green;

    sf::CircleShape yl, yr;

    if (m_useNow)
    {
        yl.setPosition(l[1].position);
        yl.setRadius(length * 0.1f);
        yl.setOrigin(yl.getRadius() * sf::Vector2f(1, 1));
        yl.setFillColor(sf::Color::Yellow);

        yr.setPosition(r[1].position);
        yr.setRadius(length * 0.1f);
        yr.setOrigin(yr.getRadius() * sf::Vector2f(1, 1));
        yr.setFillColor(sf::Color::Yellow);
    }

    sf::CircleShape cockPitCircleShape;
    cockPitCircleShape.setPosition(frontMidPoint);
    cockPitCircleShape.setRadius(length * 0.5f);
    cockPitCircleShape.setOrigin(cockPitCircleShape.getRadius() * sf::Vector2f(1, 1));
    cockPitCircleShape.setFillColor(sf::Color::Red);

    for (int i = 0; i < 4; i++) 
    {
        spaceShipMainBodyVertexArray[i].position = Math::rotateArountPoint(m_center, spaceShipMainBodyVertexArray[i].position, m_angle);
    }
    for (int i = 0; i < 3; i++)
    {
        l[i].position = Math::rotateArountPoint(m_center, l[i].position, m_angle);
        r[i].position = Math::rotateArountPoint(m_center, r[i].position, m_angle);
    }
    cockPitCircleShape.setPosition(Math::rotateArountPoint(m_center, cockPitCircleShape.getPosition(), m_angle));
    yl.setPosition(Math::rotateArountPoint(m_center, yl.getPosition(), m_angle));
    yr.setPosition(Math::rotateArountPoint(m_center, yr.getPosition(), m_angle));

    renderTarget.draw(cockPitCircleShape, renderStates);
    renderTarget.draw(l, renderStates);
    renderTarget.draw(r, renderStates);
    renderTarget.draw(yl, renderStates);
    renderTarget.draw(yr, renderStates);
    renderTarget.draw(spaceShipMainBodyVertexArray, renderStates);
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
    m_useNow = false;
    if (Math::norm(delta) > 1e-10)
    {
        delta = Math::normalize(delta) * m_speed;
        m_center += delta * dt;
        m_useNow = true;
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