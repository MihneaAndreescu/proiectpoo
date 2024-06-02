#include "Shroom.h"
#include <random>
#include <iostream>

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
    return { loadingBar, filledPart };
}

void Shroom::setPosition(sf::Vector2f position) {
    m_position = position;
}

Shroom::Shroom(float size, bool fx) : Shroom(size, size * 0.5, size * -2, fx) {}

Shroom::Shroom(float capRadius, float stalkWidth, float stalkHeight, bool fx) : m_fx(fx) {
    if (capRadius <= 0 || stalkWidth <= 0 || stalkHeight >= 0) {
        throw ShroomException("Invalid dimensions - CapRadius: " + std::to_string(capRadius) +
            ", StalkWidth: " + std::to_string(stalkWidth) +
            ", StalkHeight: " + std::to_string(stalkHeight));
    }
    m_cap.setRadius(capRadius);
    m_cap.setFillColor(sf::Color::Red);
    m_cap.setOrigin(capRadius, capRadius);
    m_stalk.setSize(sf::Vector2f(stalkWidth, stalkHeight));
    m_stalk.setFillColor(m_color.toSFMLColor());
    m_stalk.setOrigin(stalkWidth / 2, 0);
    m_stalk.setPosition(0, capRadius / 2);
}

void Shroom::update(float dt, float timeS) {
    if (dt < 0) {
        throw ShroomException("Negative dt - dt: " + std::to_string(dt));
    }
    m_timeS = timeS;
    m_elapsed += dt * 0.5;
    m_total += dt;
    if (m_elapsed >= 1) {
        m_elapsed -= 1;
        m_color = m_targetColor;
        m_targetColor = {
            RandomNumber::getInstance().getRandom(std::uniform_real_distribution<float>(0.0f, 255.0f)),
            RandomNumber::getInstance().getRandom(std::uniform_real_distribution<float>(0.0f, 255.0f)),
            RandomNumber::getInstance().getRandom(std::uniform_real_distribution<float>(0.0f, 255.0f))
        };
    }
    if (m_total >= 0) {
        m_total -= RandomNumber::getInstance().getRandom(std::uniform_real_distribution<float>(0.4f, 0.8f));
        sf::CircleShape shp;
        shp.setPosition(m_cap.getPosition() + m_position);
        shp.setFillColor(sf::Color::Transparent);
        shp.setOutlineColor(sf::Color::Red);
        shp.setOutlineThickness(0.01f);
        m_shapes.insert(m_shapes.begin(), shp);
    }
    for (auto& shp : m_shapes) {
        shp.setRadius(shp.getRadius() + dt * 0.2f);
        shp.setOrigin(shp.getRadius() * sf::Vector2f(1, 1));
        float t = shp.getRadius();
        if (t >= 1) {
            t = 1;
        }
        shp.setOutlineColor(sf::Color(35 * t + (1 - t) * 255, 100 * t + (1 - t) * 0, 44 * t + (1 - t) * 0));
    }
    while (!m_shapes.empty() && m_shapes.back().getRadius() >= 1) {
        m_shapes.pop_back();
    }
}

void Shroom::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const {
    auto stalk = m_stalk;
    auto cap = m_cap;
    DuneColor<float> currentColor; 
    if (m_fx == 0) {
        currentColor = (m_color * (1.0f - m_elapsed)) + (m_targetColor * m_elapsed);
    }
    else {
        currentColor = m_color;
    }
    cap.setFillColor(currentColor.toSFMLColor());
    cap.setPosition(cap.getPosition() + m_position);
    stalk.setPosition(stalk.getPosition() + m_position);
    renderTarget.draw(stalk, renderStates);
    renderTarget.draw(cap, renderStates);
    for (auto& circle : m_shapes) {
        renderTarget.draw(circle, renderStates);
    }
    if (m_timeS > 0.1f) {
        for (auto& shp : drawLoadingBar(cap.getPosition() + sf::Vector2f(0, 0.1f), m_timeS, sf::Vector2f(0.2f, 0.1f))) {
            renderTarget.draw(shp, renderStates);
        }
    }
}

sf::CircleShape Shroom::getCap() {
    auto cap = m_cap;
    cap.setPosition(cap.getPosition() + m_position);
    return cap;
}
