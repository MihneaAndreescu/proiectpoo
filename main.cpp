#include <iostream>
#include <array>
#include <chrono>
#include <thread>
#include <cmath>

#include <SFML/Graphics.hpp>

#include <Helper.h>

//////////////////////////////////////////////////////////////////////
/// NOTE: this include is needed for environment-specific fixes     //
/// You can remove this include and the call from main              //
/// if you have tested on all environments, and it works without it //
#include "env_fixes.h"                                              //
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
/// This class is used to test that the memory leak checks work as expected even when using a GUI
class SomeClass {
public:
    explicit SomeClass(int) {}
};

SomeClass* getC() {
    return new SomeClass{ 2 };
}
//////////////////////////////////////////////////////////////////////

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

class Planet : public sf::Drawable
{
private:
    std::string m_name;
    sf::CircleShape m_circleShape;
    sf::Vector2f m_velocity;
    float m_mass;
    sf::Vector2f m_forces;

public:
    Planet(const std::string& name, const sf::Vector2f& position, const float& radius, sf::Vector2f velocity = sf::Vector2f(0, 0), float mass = 1, sf::Texture* texture = nullptr) :
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

    Planet(const Planet& other) :
        m_name(other.m_name),
        m_circleShape(other.m_circleShape),
        m_velocity(other.m_velocity),
        m_mass(other.m_mass),
        m_forces(other.m_forces)
    {

    }

    sf::Vector2f getPosition() const
    {
        return m_circleShape.getPosition();
    }

    float getMass() const
    {
        return m_mass;
    }

    Planet operator = (const Planet& other)
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

    void applyForce(sf::Vector2f force)
    {
        m_forces += force;
    }

    void clearForces()
    {
        m_forces = sf::Vector2f(0, 0);
    }

    void setTexture(sf::Texture* texture)
    {
        m_circleShape.setTexture(texture);
    }

    ~Planet()
    {

    }

    virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const
    {
        renderTarget.draw(m_circleShape, renderStates);
    }

    friend std::ostream& operator << (std::ostream& os, const Planet& planet)
    {
        os << "(name = " << planet.m_name << " | radius = " << planet.m_circleShape.getRadius() << " | location = (" << planet.m_circleShape.getPosition().x << ", " << planet.m_circleShape.getPosition().y << "))";
        return os;
    }

    void update(float dt)
    {
        m_velocity += dt * m_forces / m_mass;
        m_circleShape.move(dt * m_velocity);
    }
};

class PlanetSystem : public sf::Drawable
{
private:
    std::string m_name;
    std::vector<Planet> m_planets;
public:
    explicit PlanetSystem(const std::string& name) :
        m_name(name)
    {
    }

    PlanetSystem(const std::string& name, const std::vector<Planet>& planets) :
        m_name(name),
        m_planets(planets)
    {
    }

    PlanetSystem(const PlanetSystem& other) :
        m_name(other.m_name),
        m_planets(other.m_planets)
    {

    }

    PlanetSystem operator = (const PlanetSystem& other)
    {
        if (this != &other)
        {
            this->m_name = other.m_name;
            this->m_planets = other.m_planets;
        }
        return *this;
    }

    ~PlanetSystem()
    {
    }

    virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const
    {
        for (const auto& planet : m_planets)
        {
            renderTarget.draw(planet, renderStates);
        }
    }

    friend std::ostream& operator << (std::ostream& os, const PlanetSystem& system)
    {
        os << "(name = " << system.m_name << " | planets = (";
        bool isFirst = true;
        for (const auto& planet : system.m_planets)
        {
            if (!isFirst)
            {
                os << ", ";
                isFirst = false;
            }
            os << planet << " ";
        }
        os << "))";
        return os;
    }

    void addPlanet(const Planet& planet)
    {
        m_planets.push_back(planet);
    }

    void update(float dt)
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
                    mag *= 0.01;
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
};

int main()
{
    sf::RenderWindow window;
    window.create(sf::VideoMode({ 900, 900 }), "Muad'dib", sf::Style::Default);
    window.setVerticalSyncEnabled(true);

    sf::Texture duneTexture;
    duneTexture.loadFromFile("..\\..\\..\\dune_texture.png");

    sf::Texture caladanTexture;
    caladanTexture.loadFromFile("..\\..\\..\\caladan_texture.png");

    sf::View view;
    view.setSize(sf::Vector2f(2, 2));
    view.setCenter(sf::Vector2f(1, 1));
    window.setView(view);



    PlanetSystem planetarySystem{ "Sistemul lu' Mihnea" };

    planetarySystem.addPlanet(Planet{ "Dune", sf::Vector2f(0.4f, 0.6f), 0.1f, sf::Vector2f(1, 1) * 0.1f, 3.0f, &duneTexture });
    planetarySystem.addPlanet(Planet{ "Caladan", sf::Vector2f(0.2f, 0.1f), 0.05f, sf::Vector2f(-1, 1) * 0.1f, 1.0f, &caladanTexture });

    init_threads();
    Helper helper;
    helper.help();

    SomeClass* c = getC();
    std::cout << c << "\n";
    delete c;



    sf::Clock fpsClock;
    sf::Clock secondClock;
    int fps = 0;

    while (window.isOpen())
    {
        bool shouldExit = false;
        sf::Event e{};
        while (window.pollEvent(e))
        {
            switch (e.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                std::cout << "New width: " << window.getSize().x << '\n'
                    << "New height: " << window.getSize().y << '\n';
                break;
            case sf::Event::KeyPressed:
                std::cout << "Received key " << (e.key.code == sf::Keyboard::X ? "X" : "(other)") << "\n";
                if (e.key.code == sf::Keyboard::Escape)
                    shouldExit = true;
                break;
            default:
                break;
            }
        }
        if (shouldExit)
        {
            window.close();
            break;
        }

        sf::CircleShape shape;
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(sf::Vector2f(0, 0));
        shape.setRadius(100);
        shape.setOrigin(sf::Vector2f(1, 1) * shape.getRadius());



        float dt = fpsClock.restart().asSeconds();
        planetarySystem.update(dt);
        if (secondClock.getElapsedTime().asSeconds() >= 1)
        {
            std::cout << "fps = " << fps << " " << planetarySystem << std::endl;
            secondClock.restart();
            fps = 0;
        }
        fps++;

        window.clear();
        window.draw(shape);
        window.draw(planetarySystem);
        window.display();
    }
    return 0;
}
