#include "Planet.h"

Planet::Planet(const std::string& name, const sf::Vector2f& position, const float& radius, sf::Vector2f velocity, float mass, sf::Texture* texture) :
    m_name(name),
    m_circleShape(radius),
    m_velocity(velocity),
    m_mass(mass),
    m_forces(sf::Vector2f(0, 0))
{
    m_circleShape.setTexture(texture);
    m_circleShape.setOrigin(sf::Vector2f(1, 1) * radius);
    m_circleShape.setPosition(position);
}

Planet::Planet(const Planet& other) :
    m_name(other.m_name),
    m_circleShape(other.m_circleShape),
    m_velocity(other.m_velocity),
    m_mass(other.m_mass),
    m_forces(other.m_forces)
{

}

sf::Vector2f Planet::getPosition() const
{
    return m_circleShape.getPosition();
}

float Planet::getMass() const
{
    return m_mass;
}

Planet Planet::operator = (const Planet& other)
{
    if (this != &other)
    {
        this->m_name = other.m_name;
        this->m_circleShape = other.m_circleShape;
        this->m_velocity = other.m_velocity;
        this->m_mass = other.m_mass;
        this->m_forces = other.m_forces;
    }
    return *this;
}

void Planet::applyForce(sf::Vector2f force)
{
    m_forces += force;
}

void Planet::clearForces()
{
    m_forces = sf::Vector2f(0, 0);
}

void Planet::setTexture(sf::Texture* texture)
{
    m_circleShape.setTexture(texture);
}

Planet::~Planet()
{

}

void Planet::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const
{
    renderTarget.draw(m_circleShape, renderStates);
}

std::ostream& operator<<(std::ostream& os, const Planet& planet) {
    os << "(name = " << planet.m_name << " | radius = " << planet.m_circleShape.getRadius() << " | location = (" << planet.m_circleShape.getPosition().x << ", " << planet.m_circleShape.getPosition().y << "))";
    return os;
}

void Planet::update(float dt)
{
    m_velocity += dt * m_forces / m_mass;
    m_circleShape.move(dt * m_velocity);
}