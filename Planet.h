#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "GravityObject.h"
#include "DuneColor.h"
#include <memory>


class Planet : public GravityObject {
private:
    std::string m_name;
    sf::CircleShape m_circleShape;
    sf::Vector2f m_velocity;
    float m_mass;
    sf::Vector2f m_forces;
public:
    sf::CircleShape getCircleShape();
    void prepDraw() override;
    Planet(const std::string& name, const sf::Vector2f& center, const float& radius, sf::Vector2f velocity, float mass, DuneColor<unsigned char> color);
    Planet(const Planet& other);
    Planet operator = (const Planet& other);
    ~Planet();
    sf::Vector2f getCenter() const override;
    float getMass() const override;
    void update(ObjectUpdateInfo m_drawInfo) override;
    void applyForce(sf::Vector2f force) override;
    void clearForces() override;
    void setTexture(sf::Texture* texture);
    void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const override;
    friend std::ostream& operator<<(std::ostream& os, const Planet& planet);
};

class PlanetBuilder {
private:
    std::string name;
    sf::Vector2f center;
    float radius;
    sf::Vector2f velocity;
    float mass;
    DuneColor<unsigned char> color;
public:

    PlanetBuilder();
    PlanetBuilder& setName(const std::string& name);
    PlanetBuilder& setCenter(const sf::Vector2f& center);
    PlanetBuilder& setRadius(float radius);
    PlanetBuilder& setVelocity(const sf::Vector2f& velocity);
    PlanetBuilder& setMass(float mass);
    PlanetBuilder& setColor(const DuneColor<unsigned char>& color);
    std::shared_ptr<Planet> build() const;
};