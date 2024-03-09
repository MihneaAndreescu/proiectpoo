#include <iostream>
#include <array>
#include <chrono>
#include <thread>

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


class Planet : public sf::Drawable
{
private:
    std::string m_name;
    sf::CircleShape m_shape;

public:
    Planet(const std::string& name, const sf::Vector2f& position, const float& radius) :
        m_name(name),
        m_shape(radius)
    {
        m_shape.setOrigin(sf::Vector2f(1, 1) * radius);
        m_shape.setPosition(position);
    }

    Planet(const std::string& name, const sf::Vector2f& position, const float& radius, sf::Texture* texture) :
        m_name(name),
        m_shape(radius)
    {
        m_shape.setTexture(texture);
        m_shape.setOrigin(sf::Vector2f(1, 1) * radius);
        m_shape.setPosition(position);
    }

    Planet(const Planet& other) :
        m_name(other.m_name),
        m_shape(other.m_shape)
    {

    }

    Planet operator = (const Planet& other)
    {
        if (this != &other)
        {
            this->m_name = other.m_name;
            this->m_shape = other.m_shape;
        }
        return *this;
    }

    void setTexture(sf::Texture* texture)
    {
        m_shape.setTexture(texture);
    }

    ~Planet()
    {

    }

    virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const
    {
        renderTarget.draw(m_shape, renderStates);
    }

    friend std::ostream& operator << (std::ostream& os, const Planet& planet)
    {
        os << "(name = " << planet.m_name << " | radius = " << planet.m_shape.getRadius() << " | location = (" << planet.m_shape.getPosition().x << ", " << planet.m_shape.getPosition().y << "))";
        return os;
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
    view.setSize(sf::Vector2f(1, 1));
    view.setCenter(sf::Vector2f(0.5, 0.5));
    window.setView(view);


    
    PlanetSystem planetarySystem{ "Sistemul lu' Mihnea" };

    planetarySystem.addPlanet(Planet{ "Dune", sf::Vector2f(0.4f, 0.6f), 0.2f, &duneTexture });
    planetarySystem.addPlanet(Planet{ "Caladan", sf::Vector2f(0.2f, 0.1f), 0.1f, &caladanTexture });

    init_threads();
    Helper helper;
    helper.help();

    SomeClass* c = getC();
    std::cout << c << "\n";
    delete c;



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
