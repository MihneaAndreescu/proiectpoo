#include "PsychedelicDrug.h"
#include "Math.h"
#include "Shroom.h"
#include <random>
#include "Math.h"
#include "RandomNumber.h"
#include "SpaceShip.h"
#include "StarObject.h"

PsychedelicDrug::PsychedelicDrug(const std::string& name) :
    m_name(name),
    m_shroom(RandomNumber::getInstance().getRandom(std::uniform_real_distribution<float>(0.1f, 0.15f))),
    m_timeSinceNotOnDrugs(0) {
    float radius = RandomNumber::getInstance().getRandom(std::uniform_real_distribution<float>(0.0f, 1.0f));
    radius = radius * radius * radius;
    radius = radius * 100;
    while (abs(radius) > 2.5) {
        radius /= 2;
    }
    float angle = RandomNumber::getInstance().getRandom(std::uniform_real_distribution<float>(0.0f, 2.0f * Math::PI));
    m_center = radius * sf::Vector2f(cos(angle), sin(angle));
    m_shroom.setPosition(m_center);
}

PsychedelicDrug::PsychedelicDrug(const PsychedelicDrug& other) :
    m_name(other.m_name),
    m_center(other.m_center),
    m_shroom(other.m_shroom),
    m_timeSinceNotOnDrugs(other.m_timeSinceNotOnDrugs) {
}

sf::Vector2f PsychedelicDrug::getCenter() const {
    return m_center;
}

PsychedelicDrug PsychedelicDrug::operator = (const PsychedelicDrug& other) {
    if (this != &other) {
        this->m_name = other.m_name;
        this->m_center = other.m_center;
        this->m_shroom = other.m_shroom;
        this->m_timeSinceNotOnDrugs = other.m_timeSinceNotOnDrugs;
    }
    return *this;
}

PsychedelicDrug::~PsychedelicDrug() {
}

void PsychedelicDrug::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const {
    renderTarget.draw(m_shroom, renderStates);
}

std::vector<std::shared_ptr<GameObject>> PsychedelicDrug::update(ObjectUpdateInfo m_updateInfo, const std::vector<std::shared_ptr<GameObject>>& allObjects) {
    for (auto& obj : allObjects) {
        obj->dummy();
    }
    m_timeSinceNotOnDrugs += m_updateInfo.deltaTime;
    m_shroom.update(m_updateInfo.deltaTime, m_timeSinceNotOnDrugs);

    std::vector<std::shared_ptr<GameObject>> nw;
    {
        sf::CircleShape circle = this->getCap();
        bool is = 0;

        for (auto& other : allObjects) {
            if (requestsDelete()) {
                continue;
            }
            auto spaceShip = std::dynamic_pointer_cast<SpaceShip>(other);
            if (spaceShip) {
                sf::RectangleShape rectangle = spaceShip->getRigidBodyBoundingBox(1);
                if (Math::intersects(rectangle, circle)) {
                    is = 1;
                    if (this->getTimeSinceNotOnDrugs() >= 1) {
                        spaceShip->increase();
                        this->rqdl = true;
                        nw.push_back(std::make_shared<StarObject>("Star 5"));
                    }
                }
            }
        }
        if (is == 0) {
            this->resetTimeSinceNotOnDrugs();
        }
    }
    return nw;
}

void PsychedelicDrug::resetTimeSinceNotOnDrugs() {
    m_timeSinceNotOnDrugs = 0;
}

void PsychedelicDrug::prepDraw() {
    m_shroom.setPosition(m_center);
}

std::ostream& operator<<(std::ostream& os, const PsychedelicDrug& planet) {
    os << "(name = " << planet.m_name << ")\n";
    return os;
}

sf::CircleShape PsychedelicDrug::getCap() {
    return m_shroom.getCap();
}

float PsychedelicDrug::getTimeSinceNotOnDrugs() {
    return m_timeSinceNotOnDrugs;
}