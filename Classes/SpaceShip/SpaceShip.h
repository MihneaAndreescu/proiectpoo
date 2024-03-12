#pragma once
#include <string>
#include <SFML/Graphics.hpp>


class SpaceShip : public sf::Drawable
{
private:
    std::string m_name;
    sf::RectangleShape m_shape;
    float m_speed;

public:
    SpaceShip(const std::string& name, const sf::Vector2f& center, const sf::Vector2f size, float speed = 1, const sf::Texture* texture = nullptr);
    SpaceShip(const SpaceShip& other);
    SpaceShip operator = (const SpaceShip& other);
    ~SpaceShip();

    sf::Vector2f getCenter() const;
    sf::Vector2f getSize() const;
    float getMass() const;

    void update(float dt);
    void setTexture(sf::Texture* texture);

    virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const;
    friend std::ostream& operator<<(std::ostream& os, const SpaceShip& SpaceShip);
};