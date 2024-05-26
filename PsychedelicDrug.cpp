#include "PsychedelicDrug.h"
#include "Math.h"
#include "Shroom.h"
#include <random>
#include "Math.h"

std::mt19937 rng(777);
std::uniform_real_distribution<float> sizeDistribution(0.1f, 0.15f);
std::uniform_real_distribution<float> distribution01(0, 1);
std::uniform_real_distribution<float> distribution02pi(0, 2 * Math::PI);

PsychedelicDrug::PsychedelicDrug(const std::string& name) :
    m_name(name),
    m_shroom(sizeDistribution(rng)) {
    float radius = distribution01(rng);
    radius = radius * radius * radius;
    radius = radius * 100;
    while (abs(radius) > 3) {
        radius /= 2;
    }
    float angle = distribution02pi(rng);
    m_center = radius * sf::Vector2f(cos(angle), sin(angle));
    m_shroom.setPosition(m_center);
}

PsychedelicDrug::PsychedelicDrug(const PsychedelicDrug& other) :
    m_name(other.m_name),
    m_center(other.m_center),
    m_shroom(other.m_shroom) {
}

sf::Vector2f PsychedelicDrug::getCenter() const {
    return m_center;
}

PsychedelicDrug PsychedelicDrug::operator = (const PsychedelicDrug& other) {
    if (this != &other) {
        this->m_name = other.m_name;
        this->m_center = other.m_center;
        this->m_shroom = other.m_shroom;
    }
    return *this;
}


PsychedelicDrug::~PsychedelicDrug() {
}

void PsychedelicDrug::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const {
    renderTarget.draw(m_shroom, renderStates);
}

void PsychedelicDrug::update(ObjectUpdateInfo m_drawInfo) {

}

void PsychedelicDrug::prepDraw() {
    m_shroom.setPosition(m_center);
}

std::ostream& operator<<(std::ostream& os, const PsychedelicDrug& planet) {
    os << "(name = " << planet.m_name << ")\n";
    return os;
}
