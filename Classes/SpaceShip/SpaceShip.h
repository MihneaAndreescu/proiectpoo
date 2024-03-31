#pragma once
#include <string>
#include <SFML/Graphics.hpp>


class SpaceShip : public sf::Drawable
{
private:
    std::string m_name;
    sf::Vector2f m_center;
    sf::Vector2f m_size;
    float m_angle;
    float m_speed;
    bool m_useNow;

    sf::Keyboard::Key m_keyUp;
    sf::Keyboard::Key m_keyDown;
    sf::Keyboard::Key m_keyLeft;
    sf::Keyboard::Key m_keyRight;

public:
    SpaceShip(const std::string& name, const sf::Vector2f& center, const sf::Vector2f size, float speed = 1);
    SpaceShip(const SpaceShip& other);
    SpaceShip operator = (const SpaceShip& other);
    ~SpaceShip();

    sf::Vector2f getCenter() const;
    sf::Vector2f getSize() const;
    float getMass() const;

    void update(float dt, sf::Vector2f mousePosition);

    void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const override;
    friend std::ostream& operator<<(std::ostream& os, const SpaceShip& SpaceShip);

    void setKeyboardKeyForUp(sf::Keyboard::Key key);
    void setKeyboardKeyForDown(sf::Keyboard::Key key);
    void setKeyboardKeyForLeft(sf::Keyboard::Key key);
    void setKeyboardKeyForRight(sf::Keyboard::Key key);
};