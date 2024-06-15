#include "Kilonova.h"
#include "Math.h"
#include "RandomNumber.h"
#include <random>
#include <cmath>
#include "DuneColor.h"

Kilonova::Kilonova(sf::Vector2f center, const std::string& name) :
    m_name(name),
    m_center(center),
    m_star(center, 0.1f),
    m_t(0) {
}

void Kilonova::update(ObjectUpdateInfo m_updateInfo, const std::vector<std::shared_ptr<GameObject>>& allObjects) {
    for (auto& obj : allObjects) {
        obj->dummy();
    }
    m_t += m_updateInfo.deltaTime;
    m_star.setAngle(m_star.getAngle() + m_updateInfo.deltaTime * 10);
}

sf::Vector2f Kilonova::getCenter() const {
    return m_center;
}

bool Kilonova::isDead() const {
    return m_t > 1;
}

void Kilonova::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const {
    renderTarget.draw(m_star, renderStates);
}

void Kilonova::prepDraw() {
    m_star.setColor(DuneColor<unsigned char>(255, 255, std::min(1 - m_t, m_t) * 2 * 255, 100));
    m_star.setSize(m_t * 1.0f);
}

DuneColor<unsigned char> Kilonova::getColor() const {
    return m_star.getColor();
}

Kilonova& Kilonova::operator=(const Kilonova& other) {
    if (this != &other) {
        m_name = other.m_name;
        m_center = other.m_center;
        m_star = other.m_star;
        m_t = other.m_t;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Kilonova& star) {
    os << "(name = " << star.m_name << ", " << star.getColor().r() << " " << star.getColor().g() << " " << star.getColor().b() << ")\n";
    return os;
}
