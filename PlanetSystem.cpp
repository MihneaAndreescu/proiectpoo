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

float pointToLineDistance(const sf::Vector2f& A, const sf::Vector2f& B, const sf::Vector2f& P) {
    sf::Vector2f AP = P - A;
    sf::Vector2f AB = B - A;
    float ab2 = AB.x * AB.x + AB.y * AB.y;
    float ap_ab = AP.x * AB.x + AP.y * AB.y;
    float t = ap_ab / ab2;
    if (t < 0.0f) {
        return std::sqrt(AP.x * AP.x + AP.y * AP.y);
    }
    else if (t > 1.0f) {
        sf::Vector2f BP = P - B;
        return std::sqrt(BP.x * BP.x + BP.y * BP.y);
    }
    else {
        sf::Vector2f Closest = A + t * AB;
        sf::Vector2f ClosestP = P - Closest;
        return std::sqrt(ClosestP.x * ClosestP.x + ClosestP.y * ClosestP.y);
    }
}

bool intersects(const sf::RectangleShape& rectangle, const sf::CircleShape& circle) {
    sf::Vector2f rectPos = rectangle.getPosition();
    sf::Vector2f circlePos = circle.getPosition();
    float radius = circle.getRadius();
    float rectWidth = rectangle.getSize().x;
    float rectHeight = rectangle.getSize().y;
    float rotation = rectangle.getRotation() * (Math::PI / 180.0);
    sf::Vector2f vertices[4];
    vertices[0] = rectPos;
    vertices[1] = sf::Vector2f(rectPos.x + rectWidth * cos(rotation), rectPos.y + rectWidth * sin(rotation));
    vertices[2] = sf::Vector2f(vertices[1].x - rectHeight * sin(rotation), vertices[1].y + rectHeight * cos(rotation));
    vertices[3] = sf::Vector2f(rectPos.x - rectHeight * sin(rotation), rectPos.y + rectHeight * cos(rotation));
    for (int i = 0; i < 4; i++) {
        int next = (i + 1) % 4;
        if (pointToLineDistance(vertices[i], vertices[next], circlePos) <= radius) {
            return true;
        }
    }
    for (int i = 0; i < 4; i++) {
        float dx = vertices[i].x - circlePos.x;
        float dy = vertices[i].y - circlePos.y;
        if (dx * dx + dy * dy <= radius * radius) {
            return true;
        }
    }
    return false;
}

bool intersects(const sf::CircleShape& a, const sf::CircleShape& b) {
    sf::Vector2f positionA = a.getPosition();
    sf::Vector2f positionB = b.getPosition();
    float deltaX = positionA.x - positionB.x;
    float deltaY = positionA.y - positionB.y;
    float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);
    float radiusA = a.getRadius();
    float radiusB = b.getRadius();
    return distance <= (radiusA + radiusB);
}

void PlanetSystem::update(ObjectUpdateInfo m_drawInfo) {
    if ((int)getObjectsOfType<PsychedelicDrug>().size() == 0) {
        addObject(std::make_shared<PsychedelicDrug>("PsychedelicDrugDrug"));
    }
    
    std::vector<std::shared_ptr<GravityObject>> gravityObjects = getObjectsOfType<GravityObject>();
    for (size_t i = 0; i < gravityObjects.size(); i++) {
        for (size_t j = 0; j < gravityObjects.size(); j++) {
            if (i != j) {
                std::shared_ptr<GravityObject> a = gravityObjects[i];
                std::shared_ptr<GravityObject> b = gravityObjects[j];
                sf::Vector2f dir = Math::normalize(b->getCenter() - a->getCenter());
                float mag = a->getMass() * b->getMass() / Math::dot(a->getCenter() - b->getCenter(), a->getCenter() - b->getCenter());
                mag *= 0.01f;
                a->applyForce(dir * mag);
            }
        }
    }
    std::vector<std::shared_ptr<SpaceShip>> spaceShips = getObjectsOfType<SpaceShip>();
    std::vector<std::shared_ptr<Planet>> planets = getObjectsOfType<Planet>();
    std::vector<std::shared_ptr<PsychedelicDrug>> drugs = getObjectsOfType<PsychedelicDrug>();
    for (auto& spaceShip : spaceShips) {
        sf::RectangleShape rectangle = spaceShip->getRigidBodyBoundingBox(0);
        for (auto& planet : planets) {
            sf::CircleShape circle = planet->getCircleShape();
            if (intersects(rectangle, circle)) {
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
            if (intersects(rectangle, circle)) {
                dels.insert(heart);
                spaceShip->increaseHearts();
                spaceShip->increase(-(spaceShip->countShrooms() / 2));
            }
        }
    }
    for (auto& object : gravityObjects) {
        sf::Vector2f dir = object->getCenter();
        object->applyForce(-Math::normalize(dir) * 1.0f * Math::norm(dir) * Math::norm(dir));
    }
    for (auto& object : m_gameObjects) {
        object->update(m_drawInfo);
    }
    std::vector<std::shared_ptr<StarObject>> starObjects = getObjectsOfType<StarObject>();
    for (int i = 0; i < (int)starObjects.size() && dels.empty(); i++) {
        for (int j = i + 1; j < (int)starObjects.size() && dels.empty(); j++) {
            if (intersects(starObjects[i]->getCircle(), starObjects[j]->getCircle())) {
                sf::Vector2f half = (starObjects[i]->getCircle().getPosition() + starObjects[j]->getCircle().getPosition()) * 0.5f;
                addObject(std::make_shared<Kilonova>(half, "kilonova"));
                //std::cout << "Kilonova!\n";
                dels.insert(starObjects[i]);
                dels.insert(starObjects[j]);
            }
        }
    }
    std::vector<std::shared_ptr<Kilonova>> kilonovaObjects = getObjectsOfType<Kilonova>();
    for (auto& kilonova : kilonovaObjects) {
        if (kilonova->isDead()) {
            dels.insert(kilonova);
            addObject(std::make_shared<HeartObject>(kilonova->getCenter(), "heart"));
        }
    }
    for (auto& heart : heartObjects) {
        if (heart->isDead()) {
            dels.insert(heart);
        }
    }
    for (auto& drug : drugs) {
        sf::CircleShape circle = drug->getCap();
        bool is = 0;
        for (auto& spaceShip : spaceShips) {
            sf::RectangleShape rectangle = spaceShip->getRigidBodyBoundingBox(1);
            if (intersects(rectangle, circle)) {
                is = 1;
                if (drug->getTimeSinceNotOnDrugs() >= 1) {
                    spaceShip->increase();
                    if (!dels.count(drug)) {
                        dels.insert(drug);
                        addObject(std::make_shared<StarObject>("Star 5"));
                    }
                }
            }
        }
        if (is == 0) {
            drug->resetTimeSinceNotOnDrugs();
        }
    }
    for (auto& object : gravityObjects) {
        object->clearForces();
    }
    if (!dels.empty()) {
        std::vector<std::shared_ptr<GameObject>> nw;
        for (auto& object : m_gameObjects) {
            if (!dels.count(object)) {
                nw.push_back(object);
            }
        }
        m_gameObjects = nw;
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