#include "PlanetSystem.h"
#include "Math.h"
#include "GravityObject.h"

PlanetSystem::PlanetSystem() {
}

PlanetSystem::~PlanetSystem() {
}

void PlanetSystem::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const {
    for (const auto& object : m_gameObjects) {
        renderTarget.draw(*object, renderStates);
    }
}

void PlanetSystem::setName(const std::string& name) {
    m_name = name;
}

PlanetSystem::PlanetSystem(const std::string& name) :
    m_name(name) {
}

PlanetSystem::PlanetSystem(const PlanetSystem& other) :
    m_name(other.m_name),
    m_gameObjects(other.m_gameObjects) {
}

void PlanetSystem::addObject(GameObject* object) {
    m_gameObjects.push_back(object);
}

void PlanetSystem::update(ObjectUpdateInfo m_drawInfo) {
    std::vector<GravityObject*> gravityObjects = getObjectsOfType<GravityObject>();
    for (size_t i = 0; i < gravityObjects.size(); i++) {
        for (size_t j = 0; j < gravityObjects.size(); j++) {
            if (i != j) {
                GravityObject* a = gravityObjects[i];
                GravityObject* b = gravityObjects[j];
                sf::Vector2f dir = Math::normalize(b->getCenter() - a->getCenter());
                float mag = a->getMass() * b->getMass() / Math::dot(a->getCenter() - b->getCenter(), a->getCenter() - b->getCenter());
                mag *= 0.01f;
                a->applyForce(dir * mag);
            }
        }
    }
    for (auto& object : m_gameObjects) {
        object->update(m_drawInfo);
    }
    for (auto& object : gravityObjects) {
        object->clearForces();
    }
}

PlanetSystem PlanetSystem::operator = (const PlanetSystem& other) {
    if (this != &other) {
        this->m_name = other.m_name;
        this->m_gameObjects = other.m_gameObjects;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const PlanetSystem& system) {
    os << "(name = " << system.m_name << "))";
    return os;
}
