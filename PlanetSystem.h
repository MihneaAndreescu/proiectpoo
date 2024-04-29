#pragma once
#include <iostream>
#include <array>
#include <chrono>
#include <thread>
#include <cmath>

#include "Planet.h"
#include "SpaceShip.h"
#include <SFML/Graphics.hpp>

class PlanetSystem : public sf::Drawable
{
private:
    std::string m_name;
    std::vector<Planet> m_planets;
    std::vector<SpaceShip> m_spaceShips;

public:
    explicit PlanetSystem(const std::string& name);
    PlanetSystem(const std::string& name, const std::vector<Planet>& planets, const std::vector<SpaceShip>& spaceShips);
    PlanetSystem(const PlanetSystem& other);
    PlanetSystem operator = (const PlanetSystem& other);
    ~PlanetSystem();

    void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const override;
    friend std::ostream& operator << (std::ostream& os, const PlanetSystem& system);


    void addPlanet(const Planet& planet);
    void addSpaceShip(const SpaceShip& spaceShip);
    void update(float dt, sf::Vector2f mousePosition);
};

