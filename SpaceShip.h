#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Math.h"

class SpaceShip : public GameObject {
private:
    struct DrawInfo {
        sf::VertexArray spaceShipMainBodyVertexArray;
        sf::CircleShape cockPitCircleShape;
        sf::VertexArray leftRocketVertexArray;
        sf::VertexArray rightRocketVertexArray;
        std::vector<sf::CircleShape> gasCircleShapes;
    };
    sf::RectangleShape m_innerRectangleShape;
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
    DrawInfo m_drawInfo;
    float m_invinc;
    void prepDrawSpaceShipMainBodyVertexArray();
    void prepDrawLeftRocket();
    void prepDrawRightRocket();
    void prepDrawRockets();
    void prepDrawCockpit();
    void prepDrawGasCircles();
    void prepDrawAddGasCircle(const sf::Vector2f& position, float length);
    void prepDrawApplyRotation();
    void resetMovementFlags();
    sf::Vector2f computeDirection(const sf::Vector2f& mousePosition, const sf::Vector2f& center);
    void updateAngle(const sf::Vector2f& direction);
    void updateMovementFlags();
    sf::Vector2f calculateDelta(const sf::Vector2f& direction, const sf::Vector2f& perpDirection);
    void applyMovement(sf::Vector2f& delta, float deltaTime);
    void updateRotationTimers(float directionCross, float deltaTime);
    void adjustSimultaneousRotation();
    int m_hearts;
public:
    int countHearts();
    void invincible(double tInvinc);
    sf::RectangleShape getRigidBodyBoundingBox();
    void prepDraw() override;
    void update(struct ObjectUpdateInfo m_drawInfo) override;
    SpaceShip(const std::string& name, const sf::Vector2f& center, const sf::Vector2f size, float speed);
    SpaceShip(const SpaceShip& other);
    SpaceShip operator = (const SpaceShip& other);
    ~SpaceShip();
    sf::Vector2f getCenter() const;
    float getMass() const;
    void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const override;
    friend std::ostream& operator<<(std::ostream& os, const SpaceShip& SpaceShip);
};