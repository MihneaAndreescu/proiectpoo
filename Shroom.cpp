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

void Shroom::update(float dt,float timeS) {
    m_timeS = timeS;
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
        std::uniform_real_distribution<float> distribution(0.2f, 0.4f);
        total -= distribution(rng) * 2;
        sf::CircleShape shp;
        shp.setPosition(m_cap.getPosition() + m_position);
        shp.setFillColor(sf::Color::Transparent);
        shp.setOutlineColor(sf::Color::Red);
        shp.setOutlineThickness(0.01f);
        shapes.insert(shapes.begin(), shp);
    }
    for (auto& shp : shapes) {
        shp.setRadius(shp.getRadius() + dt * 0.2f);
        shp.setOrigin(shp.getRadius() * sf::Vector2f(1, 1));
        float t = shp.getRadius();
        if (t >= 1) {
            t = 1;
        }
        shp.setOutlineColor(sf::Color(35 * t + (1 - t) * 255, 100 * t + (1 - t) * 0, 44 * t + (1 - t) * 0));
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

std::vector<sf::RectangleShape> drawLoadingBar(sf::Vector2f position, float completed, sf::Vector2f size) {
    if (completed < 0.0f) {
        completed = 0.0f;
    }
    if (completed > 1.0f) {
        completed = 1.0f;
    }
    sf::RectangleShape loadingBar(size);
    loadingBar.setPosition(position);
    loadingBar.setFillColor(sf::Color(50, 50, 50, 150));
    float margin = 0.02f;
    sf::RectangleShape filledPart(sf::Vector2f((size.x - 2 * margin) * completed, size.y - 2 * margin));
    filledPart.setPosition(position.x + margin, position.y + margin);
    filledPart.setFillColor(sf::Color(0, 255, 0)); 
    return {loadingBar, filledPart};
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
    if (m_timeS > 0.01f) {
        for (auto& shp : drawLoadingBar(cap.getPosition() + sf::Vector2f(0, 0.1f), m_timeS, sf::Vector2f(0.2f, 0.1f))) {
            renderTarget.draw(shp, renderStates);
        }
    }
}
