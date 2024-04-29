#pragma once
#include <string>
#include <SFML/Graphics.hpp>


class Planet : public sf::Drawable
{
private:
    std::string m_name;
    sf::CircleShape m_circleShape;
    sf::Vector2f m_velocity;
    float m_mass;
    sf::Vector2f m_forces;

public:
    Planet(const std::string& name, const sf::Vector2f& center, const float& radius, sf::Vector2f velocity, float mass, sf::Color color);
    Planet(const Planet& other);
    Planet operator = (const Planet& other);
    ~Planet();
    
    sf::Vector2f getCenter() const;
    float getMass() const;

    void update(float dt);
    void applyForce(sf::Vector2f force);
    void clearForces();
    void setTexture(sf::Texture* texture);

    void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const override;
    friend std::ostream& operator<<(std::ostream& os, const Planet& planet);
};