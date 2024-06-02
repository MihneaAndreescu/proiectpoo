#include "HeartObject.h"
#include "Math.h"
#include "RandomNumber.h"
#include <random>
#include <cmath>

HeartObject::HeartObject(sf::Vector2f center, const std::string& name) :
    m_name(name),
    m_heart(center.x, center.y, 0.1f),
    m_center(center),
    m_time(0) {
}

void HeartObject::update(ObjectUpdateInfo m_updateInfo) {
    m_time += m_updateInfo.deltaTime * 5;
}

void HeartObject::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const {
    renderTarget.draw(m_heart, renderStates);
}

#include <iostream>

void HeartObject::prepDraw() {
    float t = (cos(m_time) + 1) * 0.5f;
    float sz = 0.2 * t + 0.4 * (1 - t);
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
