#include "PlanetSystem.h"
#include "../../Math/Math.h"

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
    for (const auto& spaceShip : m_spaceShips)
    {
        renderTarget.draw(spaceShip, renderStates);
    }
}


PlanetSystem::PlanetSystem(const std::string& name) :
    m_name(name)
{
}

PlanetSystem::PlanetSystem(const std::string& name, const std::vector<Planet>& planets, const std::vector<SpaceShip>& spaceShips) :
    m_name(name),
    m_planets(planets),
    m_spaceShips(spaceShips)
{
}

PlanetSystem::PlanetSystem(const PlanetSystem& other) :
    m_name(other.m_name),
    m_planets(other.m_planets),
    m_spaceShips(other.m_spaceShips)
{

}

void PlanetSystem::addPlanet(const Planet& planet)
{
    m_planets.push_back(planet);
}

void PlanetSystem::addSpaceShip(const SpaceShip& spaceShip)
{
    m_spaceShips.push_back(spaceShip);
}

void PlanetSystem::update(float dt, sf::Vector2f mousePosition)
{
    for (size_t i = 0; i < m_planets.size(); i++)
    {
        for (size_t j = 0; j < m_planets.size(); j++)
        {
            if (i != j)
            {
                auto& a = m_planets[i];
                auto& b = m_planets[j];
                sf::Vector2f dir = Math::normalize(b.getCenter() - a.getCenter());
                float mag = a.getMass() * b.getMass() / Math::dot(a.getCenter() - b.getCenter(), a.getCenter() - b.getCenter());
                mag *= 0.01f;
                a.applyForce(dir * mag);
            }
        }
    }
    for (auto& spaceShip : m_spaceShips) 
    {
        spaceShip.update(dt, mousePosition);
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
        this->m_spaceShips = other.m_spaceShips;
    }
    return *this;
}
