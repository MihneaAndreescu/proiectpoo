#pragma once
#include <iostream>
#include <array>
#include <chrono>
#include <thread>
#include <cmath>
#include <concepts>
#include <memory>

#include "Planet.h"
#include "SpaceShip.h"
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "ObjectUpdateInfo.h"

class PlanetSystem : public sf::Drawable {
private:
    std::string m_name;
    std::vector<std::shared_ptr<GameObject>> m_gameObjects;
public:
    int countShrooms();
    int countHearts();
    template<typename DerivedType>
    requires std::derived_from<DerivedType, GameObject>
        std::vector<std::shared_ptr<DerivedType>> getObjectsOfType() const {
        std::vector<std::shared_ptr<DerivedType>> objectsOfType;
        for (const auto& object : m_gameObjects) {
            if (auto casted = std::dynamic_pointer_cast<DerivedType>(object)) {
                objectsOfType.push_back(casted);
            }
        }
        return objectsOfType;
    }
    void prepDraw();
    PlanetSystem();
    void setName(const std::string& name);
    explicit PlanetSystem(const std::string& name);
    PlanetSystem(const PlanetSystem& other);
    PlanetSystem operator = (const PlanetSystem& other);
    ~PlanetSystem();
    void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const override;
    friend std::ostream& operator << (std::ostream& os, const PlanetSystem& system);
    void addObject(std::shared_ptr<GameObject> object);
    void update(ObjectUpdateInfo m_drawInfo);
};

