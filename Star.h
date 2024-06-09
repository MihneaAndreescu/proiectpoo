#pragma once

#include <SFML/Graphics.hpp>
#include "DuneException.h"
#include "Math.h"  
#include "DuneColor.h"

class Star : public sf::Drawable {
private:
    sf::ConvexShape m_shape;
    float m_angle = 0.0f;
    DuneColor<unsigned char> m_color = DuneColor<unsigned char>(255, 255, 0);
    float m_size;
    sf::Vector2f m_position;
    static const int POINTS = 10;
    void setShape();
public:
    Star(sf::Vector2f position, float size);
    void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const override;
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition() const;
    void setSize(float size);
    float getSize() const;
    void setAngle(float angle);
    float getAngle() const;
    void setColor(const DuneColor<unsigned char>& color);
    DuneColor<unsigned char> getColor() const;
};
