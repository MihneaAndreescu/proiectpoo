#pragma once
#include <iostream>
#include <array>
#include <chrono>
#include <thread>
#include <cmath>
#include <concepts>

#include "Planet.h"
#include "SpaceShip.h"
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "ObjectUpdateInfo.h"

class PlanetSystem : public sf::Drawable {
private:
    std::string m_name;
    std::vector<GameObject*> m_gameObjects;
public:
    template<typename DerivedType> requires std::derived_from<DerivedType, GameObject> std::vector<DerivedType*> getObjectsOfType() const {
        std::vector<DerivedType*> objectsOfType;
        for (auto& object : m_gameObjects) {
            if (auto casted = dynamic_cast<DerivedType*>(object)) {
                objectsOfType.push_back(casted);
            }
        }
        return objectsOfType;
    }
    void prepDraw() {
        for (auto& object : m_gameObjects) {
            object->prepDraw();
        }
    }
    PlanetSystem();
    void setName(const std::string& name);
    explicit PlanetSystem(const std::string& name);
    PlanetSystem(const PlanetSystem& other);
    PlanetSystem operator = (const PlanetSystem& other);
    ~PlanetSystem();
    void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const override;
    friend std::ostream& operator << (std::ostream& os, const PlanetSystem& system);
    void addObject(GameObject* object);
    void update(ObjectUpdateInfo m_drawInfo);
};

