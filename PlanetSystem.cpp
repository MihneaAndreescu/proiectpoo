#include "PlanetSystem.h"
#include "Math.h"
#include "GravityObject.h"
#include "PsychedelicDrug.h"
#include "SpaceShip.h"
#include <set>
#include "DuneException.h"
#include "StarObject.h"
#include "HeartObject.h"
#include "Kilonova.h"

PlanetSystem::PlanetSystem() {
}

PlanetSystem::~PlanetSystem() {
}

void PlanetSystem::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const {
    for (const auto& object : m_gameObjects) {
        if (!std::dynamic_pointer_cast<SpaceShip>(object)) {
            renderTarget.draw(*object, renderStates);
        }
    }
    for (const auto& object : m_gameObjects) {
        if (std::dynamic_pointer_cast<SpaceShip>(object)) {
            renderTarget.draw(*object, renderStates);
        }
    }
}

void PlanetSystem::prepDraw() {
    for (auto& object : m_gameObjects) {
        object->prepDraw();
    }
}

void PlanetSystem::setName(const std::string& name) {
    m_name = name;
    if (name.empty()) {
        throw PlanetSystemInitializationException("nume gol");
    }
}

PlanetSystem::PlanetSystem(const std::string& name) :
    m_name(name) {
}

PlanetSystem::PlanetSystem(const PlanetSystem& other) :
    m_name(other.m_name),
    m_gameObjects(other.m_gameObjects) {
}

void PlanetSystem::addObject(std::shared_ptr<GameObject> object) {
    m_gameObjects.push_back(object);
}

void PlanetSystem::update(ObjectUpdateInfo m_updateInfo) {
    if ((int)getObjectsOfType<PsychedelicDrug>().size() == 0) {
        addObject(std::make_shared<PsychedelicDrug>("PsychedelicDrugDrug"));
    }
    std::vector<std::shared_ptr<SpaceShip>> spaceShips = getObjectsOfType<SpaceShip>();
    std::vector<std::shared_ptr<Planet>> planets = getObjectsOfType<Planet>();
    for (auto& spaceShip : spaceShips) {
        sf::RectangleShape rectangle = spaceShip->getRigidBodyBoundingBox(0);
        for (auto& planet : planets) {
            sf::CircleShape circle = planet->getCircleShape();
            if (Math::intersects(rectangle, circle)) {
                spaceShip->invincible(5);
            }
        }
    }
    std::vector<std::shared_ptr<HeartObject>> heartObjects = getObjectsOfType<HeartObject>();
    std::set<std::shared_ptr<GameObject>> dels;
    for (auto& spaceShip : spaceShips) {
        sf::RectangleShape rectangle = spaceShip->getRigidBodyBoundingBox(1);
        for (auto& heart : heartObjects) {
            sf::CircleShape circle = heart->getCircle();
            if (Math::intersects(rectangle, circle)) {
                dels.insert(heart);
                spaceShip->increaseHearts();
                spaceShip->increase(-(spaceShip->countShrooms() / 2));
            }
        }
    }
    std::vector<std::shared_ptr<GameObject>> nw;
    for (auto& object : m_gameObjects) {
        auto now = object->update(m_updateInfo, m_gameObjects);
        for (auto& nwFrom : now) {
            nw.push_back(nwFrom);
        }
    }
    for (auto& obj : nw) {
        addObject(obj);
    }
    for (auto& object : m_gameObjects) {
        if (object->requestsDelete()) {
            dels.insert(object);
        }
    }
    if (!dels.empty()) {
        std::vector<std::shared_ptr<GameObject>> nwVec;
        for (auto& object : m_gameObjects) {
            if (!dels.count(object)) {
                nwVec.push_back(object);
            }
        }
        m_gameObjects = nwVec;
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

int PlanetSystem::countHearts() {
    std::vector<std::shared_ptr<SpaceShip>> spaceShips = getObjectsOfType<SpaceShip>();
    int sum = 0;
    for (auto& spaceShip : spaceShips) {
        sum += spaceShip->countHearts();
    }
    return sum;
}

int PlanetSystem::countShrooms() {
    std::vector<std::shared_ptr<SpaceShip>> spaceShips = getObjectsOfType<SpaceShip>();
    int sum = 0;
    for (auto& spaceShip : spaceShips) {
        sum += spaceShip->countShrooms();
    }
    return sum;
}