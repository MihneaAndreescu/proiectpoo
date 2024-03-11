#include "PlanetSystem.h"

float dot(sf::Vector2f a, sf::Vector2f b)
{
    return a.x * b.x + a.y * b.y;
}

float norm(sf::Vector2f a)
{
    return sqrt(dot(a, a));
}

sf::Vector2f normalize(sf::Vector2f a)
{
    return a / norm(a);
}


PlanetSystem::~PlanetSystem()
{

}

std::ostream& operator<<(std::ostream& os, const PlanetSystem& system)
{
    os << "(name = " << system.m_name << " | planets = (";
    bool isFirst = true;
    for (const auto& planet : system.m_planets)
    {
        if (!isFirst)
        {
            os << ", ";
        }
        isFirst = false;

        os << planet << " ";
    }
    os << "))";
    return os;
}

void PlanetSystem::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const
{
    for (const auto& planet : m_planets)
    {
        renderTarget.draw(planet, renderStates);
    }
}


PlanetSystem::PlanetSystem(const std::string& name) :
    m_name(name)
{
}

PlanetSystem::PlanetSystem(const std::string& name, const std::vector<Planet>& planets) :
    m_name(name),
    m_planets(planets)
{
}

PlanetSystem::PlanetSystem(const PlanetSystem& other) :
    m_name(other.m_name),
    m_planets(other.m_planets)
{

}

void PlanetSystem::addPlanet(const Planet& planet)
{
    m_planets.push_back(planet);
}

void PlanetSystem::update(float dt)
{
    for (size_t i = 0; i < m_planets.size(); i++)
    {
        for (size_t j = 0; j < m_planets.size(); j++)
        {
            if (i != j)
            {
                auto& a = m_planets[i];
                auto& b = m_planets[j];
                sf::Vector2f dir = normalize(b.getPosition() - a.getPosition());
                float mag = a.getMass() * b.getMass() / dot(a.getPosition() - b.getPosition(), a.getPosition() - b.getPosition());
                mag *= 0.01f;
                a.applyForce(dir * mag);
            }
        }
    }
    for (auto& planet : m_planets)
    {
        planet.update(dt);
        planet.clearForces();
    }
}

PlanetSystem PlanetSystem::operator = (const PlanetSystem& other)
{
    if (this != &other)
    {
        this->m_name = other.m_name;
        this->m_planets = other.m_planets;
    }
    return *this;
}
