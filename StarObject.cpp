#include "StarObject.h"
#include "Math.h"
#include "RandomNumber.h"
#include <random>
#include <cmath>
#include "DuneColor.h"
#include "Kilonova.h"

StarObject::StarObject(const std::string& name) :
    m_name(name),
    m_star(sf::Vector2f(0, 0), 0.1f),
    m_t(RandomNumber::getInstance().getRandom(std::uniform_real_distribution<float>(0.0f, 1.0f))),
    m_speed(RandomNumber::getInstance().getRandom(std::uniform_real_distribution<float>(0.5f, 0.7f))) {
    std::uniform_real_distribution<float> dist(-3.0f, 3.0f);
    m_center = sf::Vector2f(RandomNumber::getInstance().getRandom(dist), RandomNumber::getInstance().getRandom(dist));
    m_controlPoint1 = sf::Vector2f(RandomNumber::getInstance().getRandom(dist), RandomNumber::getInstance().getRandom(dist));
    m_controlPoint2 = sf::Vector2f(RandomNumber::getInstance().getRandom(dist), RandomNumber::getInstance().getRandom(dist));
}

std::vector<std::shared_ptr<GameObject>> StarObject::update(ObjectUpdateInfo m_updateInfo, const std::vector<std::shared_ptr<GameObject>>& allObjects) {
    m_t += m_updateInfo.deltaTime * m_speed;
    m_star.setAngle(m_star.getAngle() + m_updateInfo.deltaTime);
    if (m_t > 1.0f) {
        m_t = 0.0f;
        m_speed = RandomNumber::getInstance().getRandom(std::uniform_real_distribution<float>(0.5f, 0.7f));
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

    std::vector<std::shared_ptr<GameObject>> nw;

    for (auto& other : allObjects) {
        if (this->requestsDelete()) {
            break;
        }
        auto otherStarObject = std::dynamic_pointer_cast<StarObject>(other);
        if (otherStarObject && otherStarObject->getId() != this->getId() && Math::intersects(this->getCircle(), otherStarObject->getCircle()) && !otherStarObject->requestsDelete()) {
            sf::Vector2f half = (this->getCircle().getPosition() + otherStarObject->getCircle().getPosition()) * 0.5f;
            nw.push_back(std::make_shared<Kilonova>(half, "kilonova"));
            this->reqdl = otherStarObject->reqdl = true;
        }
    }

    return nw;
}

sf::CircleShape StarObject::getCircle() const {
    sf::CircleShape shp;
    shp.setRadius(0.1f);
    shp.setOrigin(shp.getRadius() * sf::Vector2f(1, 1));
    shp.setPosition(m_star.getPosition());
    return shp;
}

void StarObject::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const {
    renderTarget.draw(m_star, renderStates);
}

void StarObject::prepDraw() {
    m_star.setColor(DuneColor<unsigned char>(255, 255, std::min(1 - m_t, m_t) * 2 * 255));
}

DuneColor<unsigned char> StarObject::getColor() const {
    return m_star.getColor();
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

std::ostream& operator<<(std::ostream& os, const StarObject& star) {
    os << "(name = " << star.m_name << ", " << star.getColor().r() << " " << star.getColor().g() << " " << star.getColor().b() << ")\n";
    return os;
}
