#include "SpaceShip.h"

SpaceShip::SpaceShip(const std::string& name, const sf::Vector2f& center, const sf::Vector2f size, float speed, const sf::Texture* texture) :
    m_name(name),
    m_speed(speed)
{
    m_shape.setTexture(texture);
    m_shape.setSize(size);
    m_shape.setPosition(center - m_shape.getSize() * 0.5f);
}

SpaceShip::SpaceShip(const SpaceShip& other) :
    m_name(other.m_name),
    m_shape(other.m_shape),
    m_speed(other.m_speed)
{

}

SpaceShip SpaceShip::operator = (const SpaceShip& other)
{
    if (this != &other)
    {
        this->m_name = other.m_name;
        this->m_shape = other.m_shape;
        this->m_speed = other.m_speed;
    }
    return *this;
}

sf::Vector2f SpaceShip::getCenter() const
{
    return m_shape.getPosition() + m_shape.getSize() * 0.5f;
}

sf::Vector2f SpaceShip::getSize() const
{
    return m_shape.getSize();
}

\

void SpaceShip::setTexture(sf::Texture* texture)
{
    m_shape.setTexture(texture);
}

SpaceShip::~SpaceShip()
{

}

void SpaceShip::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const
{
    renderTarget.draw(m_shape, renderStates);
}

std::ostream& operator<<(std::ostream& os, const SpaceShip& spaceShip) 
{
    os << "(name = " << spaceShip.m_name << ")";
    return os;
}

void SpaceShip::update(float dt)
{
    sf::Vector2f delta = sf::Vector2f(0, 0);
    if (sf::Keyboard::isKeyPressed(m_keyUp))
    {
        delta += sf::Vector2f(0, 1);
    }
    if (sf::Keyboard::isKeyPressed(m_keyDown))
    {
        delta += sf::Vector2f(0, -1);
    }
    if (sf::Keyboard::isKeyPressed(m_keyLeft))
    {
        delta += sf::Vector2f(-1, 0);
    }
    if (sf::Keyboard::isKeyPressed(m_keyRight))
    {
        delta += sf::Vector2f(1, 0);
    }
    m_shape.move(delta * dt);
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