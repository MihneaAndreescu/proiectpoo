#include "SpaceShip.h"
#include "PlanetSystem.h"
#include "Planet.h"

#include <iostream>
#include <array>
#include <chrono>
#include <thread>
#include <cmath>

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "GravityObject.h"

#include <Helper.h>

//////////////////////////////////////////////////////////////////////
/// NOTE: this include is needed for environment-specific fixes     //
/// You can remove this include and the call from main              //
/// if you have tested on all environments, and it works without it //
#include "env_fixes.h"                                              //
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////


int main()
{
    sf::RenderWindow window;
    window.create(sf::VideoMode({ 900, 900 }), "Muad'dib", sf::Style::Default);
    window.setVerticalSyncEnabled(true);

    sf::View view;
    view.setSize(sf::Vector2f(2, -2));
    view.setCenter(sf::Vector2f(1, 1));
    window.setView(view);

    PlanetSystem planetarySystem{ "Sistemul lu' Mihnea" };
  
    planetarySystem.addObject(new SpaceShip{ "Dune", sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.2f, 0.4f), 1.0f });
    planetarySystem.addObject(new Planet{ "Dune", sf::Vector2f(0.5f, 0.5f), 0.1f, sf::Vector2f(0.0f, 0.3f), 2.0f, sf::Color::Red });
    planetarySystem.addObject(new Planet{ "Caladan", sf::Vector2f(0.2f, 0.1f), 0.05f, sf::Vector2f(0.0f, 0.1f), 4.0f, sf::Color::Blue });

   
    init_threads();
    Helper helper;
    helper.help();


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
                break;
            case sf::Event::KeyPressed:
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
        
        sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        planetarySystem.update(dt, mousePosition);

        //spaceShip.update(dt, mousePosition);

        if (secondClock.getElapsedTime().asSeconds() >= 1)
        {
            std::cout << "fps = " << fps << " " << planetarySystem << std::endl;
            secondClock.restart();
            fps = 0;
        }
        fps++;

        window.clear();
        window.draw(planetarySystem);
        window.display();
    }
    return 0;
}