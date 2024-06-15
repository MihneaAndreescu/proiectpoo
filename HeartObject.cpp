#include "HeartObject.h"
#include "Math.h"
#include "RandomNumber.h"
#include <random>
#include <cmath>
#include "DuneColor.h"

HeartObject::HeartObject(sf::Vector2f center, const std::string& name) :
    m_name(name),
    m_center(center),
    m_heart(center.x, center.y, 0.1f),
    m_time(0) {
}

sf::CircleShape HeartObject::getCircle() const{
    sf::CircleShape s;
    float t = (cos(m_time) + 1) * 0.5f;
    float sz = 0.2f * t + 0.4f * (1 - t);
    sz *= 0.4f;
    s.setRadius(sz);
    s.setOrigin(sf::Vector2f(1, 1) * sz);
    s.setPosition(m_center);
    s.setFillColor(DuneColor<unsigned char>(0, 255, 0, 100));
    return s;
}

sf::Vector2f HeartObject::getCenter() const {
    return m_center;
}

void HeartObject::update(ObjectUpdateInfo m_updateInfo, const std::vector<std::shared_ptr<GameObject>>& allObjects) {
    for (auto& obj : allObjects) {
        obj->dummy();
    }
    m_time += m_updateInfo.deltaTime * 5;
}

bool HeartObject::isDead() const {
    return m_time >= 25.0f;
}

void HeartObject::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const {
    renderTarget.draw(m_heart, renderStates);
}

void HeartObject::prepDraw() {
    float t = (cos(m_time) + 1) * 0.5f;
    float sz = 0.2f * t + 0.4f * (1 - t);
    m_heart.reConstruct(m_center.x, m_center.y, sz);
}

HeartObject& HeartObject::operator=(const HeartObject& other) {
    if (this != &other) {
        m_name = other.m_name;
        m_center = other.m_center;
        m_heart = other.m_heart;
        m_time = other.m_time;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const HeartObject& heart) {
    os << "(name = " << heart.m_name << ")\n";
    return os;
}
