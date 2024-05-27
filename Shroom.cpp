#include "Shroom.h"
#include <random>

void Shroom::setPosition(sf::Vector2f position) {
    m_position = position;
}

Shroom::Shroom(float size) : Shroom(size, size * 0.5, -size * 2) {

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
    elapsed += dt * 0.5;
    total += dt;
    if (elapsed >= 1) {
        elapsed -= 1;
        r = rtarget;
        g = gtarget;
        b = btarget;
        std::mt19937 rng((long long)(new char));
        std::uniform_real_distribution<float> distribution256(0, 255);
        rtarget = distribution256(rng);
        gtarget = distribution256(rng);
        btarget = distribution256(rng);
    }
    if (total >= 0) {
        std::mt19937 rng((long long)(new char));
        std::uniform_real_distribution<float> distribution(0.2, 0.4);
        total -= distribution(rng) * 2;
        sf::CircleShape shp;
        shp.setPosition(m_cap.getPosition() + m_position);
        shp.setFillColor(sf::Color::Transparent);
        shp.setOutlineColor(sf::Color::Red);
        shp.setOutlineThickness(0.01);
        shapes.insert(shapes.begin(), shp);
    }
    for (auto& shp : shapes) {
        shp.setRadius(shp.getRadius() + dt * 0.2);
        shp.setOrigin(shp.getRadius() * sf::Vector2f(1, 1));
        float t = shp.getRadius();
        if (t >= 1) {
            t = 1;
        }
        shp.setOutlineColor(sf::Color(35 * t + (1 - t) * 255, 100 * t + (1 - t) * 0, 300 * t + (1 - t) * 0));
    }
    while (!shapes.empty() && shapes.back().getRadius() >= 1) {
        shapes.pop_back();
    }
}

sf::CircleShape Shroom::getCap() {
    auto cap = m_cap;
    cap.setPosition(cap.getPosition() + m_position);
    return cap;
}

void Shroom::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const {
    auto stalk = m_stalk;
    auto cap = m_cap;
    cap.setFillColor(sf::Color(r * (1 - elapsed) + rtarget * elapsed, g * (1 - elapsed) + gtarget * elapsed, b * (1 - elapsed) + btarget * elapsed));
    cap.setPosition(cap.getPosition() + m_position);
    stalk.setPosition(stalk.getPosition() + m_position);
    renderTarget.draw(stalk, renderStates);
    renderTarget.draw(cap, renderStates);
    for (auto& circle : shapes) {
        renderTarget.draw(circle, renderStates);
    }
}
