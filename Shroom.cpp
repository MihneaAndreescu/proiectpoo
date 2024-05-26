#include "Shroom.h"

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
    m_stalk.setFillColor(sf::Color(139, 69, 19));
    m_stalk.setOrigin(stalkWidth / 2, 0);
    m_stalk.setPosition(0, capRadius / 2);
}

void Shroom::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const {
    auto stalk = m_stalk;
    auto cap = m_cap;
    stalk.setPosition(stalk.getPosition() + m_position);
    cap.setPosition(cap.getPosition() + m_position);
    renderTarget.draw(stalk, renderStates);
    renderTarget.draw(cap, renderStates);
}
