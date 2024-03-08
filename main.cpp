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


class Planet
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

    ~Planet()
    {

    }

    void display(sf::RenderWindow& renderWindow)
    {
        renderWindow.draw(m_shape);
    }

    friend std::ostream& operator << (std::ostream& os, const Planet& planet)
    {
        os << "(name = " << planet.m_name << " | radius = " << planet.m_shape.getRadius() << " | location = (" << planet.m_shape.getPosition().x << ", " << planet.m_shape.getPosition().y << "))";
        return os;
    }
};

int main()
{
    Planet dune{ "Dune", sf::Vector2f(0.4f, 0.6f), 0.2f };


    init_threads();
    Helper helper;
    helper.help();

    SomeClass* c = getC();
    std::cout << c << "\n";
    delete c;

    sf::RenderWindow window;
    window.create(sf::VideoMode({ 900, 900 }), "Muad'dib", sf::Style::Default);
    window.setVerticalSyncEnabled(true);

    sf::View view;
    view.setSize(sf::Vector2f(1, 1));
    view.setCenter(sf::Vector2f(0.5, 0.5));
    window.setView(view);

    sf::Clock secondClock;
    int fps = 0;

    while (window.isOpen())
    {
        bool shouldExit = false;
        sf::Event e{};
        while (window.pollEvent(e)) {
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
        if (shouldExit) {
            window.close();
            break;
        }



        if (secondClock.getElapsedTime().asSeconds() >= 1)
        {
            std::cout << "fps = " << fps << " " << dune << std::endl;
            secondClock.restart();
            fps = 0;
        }
        fps++;



        window.clear();
        dune.display(window);
        window.display();
    }
    return 0;
}
