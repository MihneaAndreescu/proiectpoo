#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "GravityObject.h"
#include "Star.h"

class StarObject : public GameObject {
private:
    std::string m_name;
    sf::Vector2f m_center;
    Star m_star;
    sf::Vector2f m_controlPoint1, m_controlPoint2;
    float m_t;  
    float m_speed;
public:
    explicit StarObject(const std::string& name);
    StarObject(const StarObject& other);
    sf::Vector2f getCenter() const;
    void update(ObjectUpdateInfo m_updateInfo) override;
    void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const override;
    void prepDraw() override;
    StarObject& operator=(const StarObject& other);
    friend std::ostream& operator<<(std::ostream& os, const StarObject& planet);
    DuneColor<unsigned char> getColor() const;
    sf::CircleShape getCircle() const;
};
