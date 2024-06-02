#include "StarObject.h"
#include "Math.h"
#include "RandomNumber.h"
#include <random>
#include <cmath>

StarObject::StarObject(const std::string& name) :
    m_name(name),
    m_star(sf::Vector2f(0, 0), 0.1f),
    m_t(RandomNumber::getInstance().getRandom(std::uniform_real_distribution<float>(0, 1))),
    m_speed(RandomNumber::getInstance().getRandom(std::uniform_real_distribution<float>(0.5, 0.7)))  {
    std::uniform_real_distribution<float> dist(-3.0f, 3.0f);
    m_center = sf::Vector2f(RandomNumber::getInstance().getRandom(dist), RandomNumber::getInstance().getRandom(dist));
    m_controlPoint1 = sf::Vector2f(RandomNumber::getInstance().getRandom(dist), RandomNumber::getInstance().getRandom(dist));
    m_controlPoint2 = sf::Vector2f(RandomNumber::getInstance().getRandom(dist), RandomNumber::getInstance().getRandom(dist));
}

void StarObject::update(ObjectUpdateInfo m_updateInfo) {
    m_t += m_updateInfo.deltaTime * m_speed;
    m_star.setAngle(m_star.getAngle() + m_updateInfo.deltaTime);
    if (m_t > 1.0f) {
        m_t = 0.0f;
        m_speed = RandomNumber::getInstance().getRandom(std::uniform_real_distribution<float>(0.5, 0.7));
        std::uniform_real_distribution<float> dist(-3.0f, 3.0f);
        m_controlPoint1 = sf::Vector2f(RandomNumber::getInstance().getRandom(dist), RandomNumber::getInstance().getRandom(dist));
        m_controlPoint2 = sf::Vector2f(RandomNumber::getInstance().getRandom(dist), RandomNumber::getInstance().getRandom(dist));
    }
    sf::Vector2f p0 = m_center;
    sf::Vector2f p1 = m_controlPoint1;
    sf::Vector2f p2 = m_controlPoint2;
    sf::Vector2f p3 = m_center;
    float u = 1 - m_t;
    float tt = m_t * m_t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * m_t;
    sf::Vector2f newPos = uuu * p0 + 3 * uu * m_t * p1 + 3 * u * tt * p2 + ttt * p3;
    m_star.setPosition(newPos);
}

void StarObject::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const {
    renderTarget.draw(m_star, renderStates);
}

void StarObject::prepDraw() {
    //m_star.setPosition(m_center);
}

StarObject& StarObject::operator=(const StarObject& other) {
    if (this != &other) {
        m_name = other.m_name;
        m_center = other.m_center;
        m_star = other.m_star;
        m_controlPoint1 = other.m_controlPoint1;
        m_controlPoint2 = other.m_controlPoint2;
        m_t = other.m_t;
        m_speed = other.m_speed;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const StarObject& planet) {
    os << "(name = " << planet.m_name << ")\n";
    return os;
}
