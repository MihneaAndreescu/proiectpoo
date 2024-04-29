#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class SpaceShip : public sf::Drawable {
private:
    std::string m_name;
    sf::Vector2f m_center;
    sf::Vector2f m_size;
    float m_speed;
    float m_angle;
    bool m_movingForward;
    bool m_movingClockwise;
    bool m_movingCounterClockwise;
    sf::Vector2f m_lastDirection;
    double m_elapsedClockwise;
    double m_elapsedCounterClockwise;
public:
    SpaceShip(const std::string& name, const sf::Vector2f& center, const sf::Vector2f size, float speed);
    SpaceShip(const SpaceShip& other);
    SpaceShip operator = (const SpaceShip& other);
    ~SpaceShip();
    sf::Vector2f getCenter() const;
    float getMass() const;
    void update(float dt, sf::Vector2f mousePosition);
    void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const override;
    friend std::ostream& operator<<(std::ostream& os, const SpaceShip& SpaceShip);
};