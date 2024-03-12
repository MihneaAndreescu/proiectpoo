#include "Classes/SpaceShip/SpaceShip.h"
#include "Classes/PlanetSystem/PlanetSystem.h"
#include "Classes/Planet/Planet.h"

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
    view.setSize(sf::Vector2f(2, -2));
    view.setCenter(sf::Vector2f(1, 1));
    window.setView(view);

    PlanetSystem planetarySystem{ "Sistemul lu' Mihnea" };
    SpaceShip spaceShip = SpaceShip{ "Dune", sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.2f, 0.4f), sf::Vector2f(0, 0.5f), 20.0f, &caladanTexture };

    //planetarySystem.addPlanet(Planet{ "Dune", sf::Vector2f(0.0f, 0.0f), 0.1f, sf::Vector2f(0, 0.5f), 20.0f, &duneTexture });
    planetarySystem.addPlanet(Planet{ "Dune", sf::Vector2f(0.5f, 0.5f), 0.1f, sf::Vector2f(0, 0.3), 2.0f, &duneTexture });
    planetarySystem.addPlanet(Planet{ "Caladan", sf::Vector2f(0.2f, 0.1f), 0.05f, sf::Vector2f(0, 0.2) * 0.5f, 4.0f, &caladanTexture });
    //planetarySystem.addPlanet(Planet{ "Caladan2", sf::Vector2f(1.2f, 1.1f), 0.05f, sf::Vector2f(1, -1) * 0.02f, 1.0f, &caladanTexture });

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
        float dt = fpsClock.restart().asSeconds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            view.move(sf::Vector2f(1, 0) * dt);
            window.setView(view);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            view.move(sf::Vector2f(-1, 0) * dt);
            window.setView(view);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            view.move(sf::Vector2f(0,1) * dt);
            window.setView(view);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            view.move(sf::Vector2f(0,-1) * dt);
            window.setView(view);
        }
        sf::CircleShape shape;
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(sf::Vector2f(0, 0));
        shape.setRadius(100);
        shape.setOrigin(sf::Vector2f(1, 1) * shape.getRadius());



        planetarySystem.update(dt);
        spaceShip.update(dt);
        if (secondClock.getElapsedTime().asSeconds() >= 1)
        {
            std::cout << "fps = " << fps << " " << planetarySystem << std::endl;
            secondClock.restart();
            fps = 0;
        }
        fps++;

        window.clear();
        window.draw(shape);
        window.draw(spaceShip);
        window.draw(planetarySystem);
        window.display();
    }
    return 0;
}
/*
--SELECT RTRIM ('XinfoXxXaabc', 'bacX') from dual;
--select TRANSLATE('$aa$aa', '$ad', 'bc') from dual;

--select to_char(to_date('07-03-2024', 'dd-mm-yyyy') + 169, 'dd-mm-yyyy') from dual;

--select concat(str1, str2) || 'castiga' || salary

select concat(concat(first_name, ' '), last_name) || ' castiga ' || salary || ' dar doreste ' || salary * 3 "Salariul ideal"

from employees;


*/