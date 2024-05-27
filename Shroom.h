#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Shroom : public sf::Drawable, public sf::Transformable {
private:
    sf::CircleShape m_cap;
    sf::RectangleShape m_stalk;
    sf::Vector2f m_position;
    float r = 200;
    float g = 100;
    float b = 30;
    float rtarget = 0;
    float gtarget = 0;
    float btarget = 0;
    float elapsed = 2;
    float total = 0;
    std::vector<sf::CircleShape> shapes;
public:
    void update(float dt);
    void setPosition(sf::Vector2f position);
    explicit Shroom(float size);
    Shroom(float capRadius, float stalkWidth, float stalkHeight);
    void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const override;
    sf::CircleShape getCap();
};
