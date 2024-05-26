#include "Shroom.h"
#include <random>

void Shroom::setPosition(sf::Vector2f position) {
    m_position = position;
}

Shroom::Shroom(float size) : Shroom(size, size * 0.5, -size * 5) {

}

Shroom::Shroom(float capRadius, float stalkWidth, float stalkHeight) {
    m_cap.setRadius(capRadius);
    m_cap.setFillColor(sf::Color::Red);
    m_cap.setOrigin(capRadius, capRadius);
    m_stalk.setSize(sf::Vector2f(stalkWidth, stalkHeight));
    m_stalk.setFillColor(sf::Color(r, g, b));
    m_stalk.setOrigin(stalkWidth / 2, 0);
    m_stalk.setPosition(0, capRadius / 2);
}


void Shroom::update(float dt) {
    std::mt19937 rng(228);
    std::uniform_real_distribution<float> distributionNegative1010(-10, 10);

    r += distributionNegative1010(rng) * dt * 10;
    g += distributionNegative1010(rng) * dt * 10;
    b += distributionNegative1010(rng) * dt * 10;
    r = std::min(200.0f, std::max(r, 50.0f));
    g = std::min(200.0f, std::max(g, 50.0f));
    b = std::min(200.0f, std::max(b, 50.0f));

}

void Shroom::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const {
    auto stalk = m_stalk;
    auto cap = m_cap;
    cap.setFillColor(sf::Color(r, g, b));
    stalk.setPosition(stalk.getPosition() + m_position);
    cap.setPosition(cap.getPosition() + m_position);
    renderTarget.draw(stalk, renderStates);
    renderTarget.draw(cap, renderStates);
}
