#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "DuneColor.h"
#include "DuneExceptions.h"
#include "RandomNumber.h"

class Shroom : public sf::Drawable, public sf::Transformable {
private:
    sf::CircleShape m_cap;
    sf::RectangleShape m_stalk;
    sf::Vector2f m_position;
    DuneColor<float> m_color = { 200, 100, 30, 255 };
    DuneColor<float> m_targetColor = { 0, 0, 0, 255 };
    float elapsed = 2;
    float total = 0;
    float m_timeS = 0;
    std::vector<sf::CircleShape> shapes;

public:
    void update(float dt, float timeS);
    void setPosition(sf::Vector2f position);
    explicit Shroom(float size);
    Shroom(float capRadius, float stalkWidth, float stalkHeight);
    void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const override;
    sf::CircleShape getCap();
};
