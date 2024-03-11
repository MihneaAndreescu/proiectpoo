#pragma once
#include <iostream>
#include <array>
#include <chrono>
#include <thread>
#include <cmath>

#include "../Planet/Planet.h"
#include <SFML/Graphics.hpp>

class PlanetSystem : public sf::Drawable
{
private:
    std::string m_name;
    std::vector<Planet> m_planets;
public:
    explicit PlanetSystem(const std::string& name);
    PlanetSystem(const std::string& name, const std::vector<Planet>& planets);
    PlanetSystem(const PlanetSystem& other);
    PlanetSystem operator = (const PlanetSystem& other);
    ~PlanetSystem();

    virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const;
    friend std::ostream& operator << (std::ostream& os, const PlanetSystem& system);

    void addPlanet(const Planet& planet);
    void update(float dt);
};

