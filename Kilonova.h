#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "GravityObject.h"
#include "Star.h"

class Kilonova : public GameObject {
private:
    std::string m_name;
    sf::Vector2f m_center;
    Star m_star;
    float m_t;
public:
    explicit Kilonova(sf::Vector2f center,const std::string& name);
    Kilonova(const Kilonova& other);
    sf::Vector2f getCenter() const;
    void update(ObjectUpdateInfo m_updateInfo) override;
    void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const override;
    void prepDraw() override;
    Kilonova& operator=(const Kilonova& other);
    friend std::ostream& operator<<(std::ostream& os, const Kilonova& planet);
    sf::Color getColor() const;
    sf::CircleShape getCircle() const;
    bool isDead() const;
};
