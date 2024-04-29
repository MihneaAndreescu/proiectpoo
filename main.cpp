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
#include "ObjectUpdateInfo.h"
//////////////////////////////////////////////////////////////////////
/// NOTE: this include is needed for environment-specific fixes     //
/// You can remove this include and the call from main              //
/// if you have tested on all environments, and it works without it //
#include "env_fixes.h"                                              //
//////////////////////////////////////////////////////////////////////
int main() {
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
    while (window.isOpen()) {
        bool shouldExit = false;
        sf::Event e{};
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window.close();
            }
            if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) {
                shouldExit = true;
            }
        }
        if (shouldExit) {
            window.close();
            break;
        }
        float dt = fpsClock.restart().asSeconds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            view.move(sf::Vector2f(1, 0) * dt);
            window.setView(view);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            view.move(sf::Vector2f(-1, 0) * dt);
            window.setView(view);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            view.move(sf::Vector2f(0, 1) * dt);
            window.setView(view);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            view.move(sf::Vector2f(0, -1) * dt);
            window.setView(view);
        }
        sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        ObjectUpdateInfo updateInfo({ dt, mousePosition });
        planetarySystem.update(updateInfo);
        if (secondClock.getElapsedTime().asSeconds() >= 1) {
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