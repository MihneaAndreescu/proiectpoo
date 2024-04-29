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

public:
    void prepDrawSpaceShipMainBodyVertexArray() {
        m_drawInfo.spaceShipMainBodyVertexArray.clear();
        m_drawInfo.spaceShipMainBodyVertexArray.setPrimitiveType(sf::Quads);
        m_drawInfo.spaceShipMainBodyVertexArray.append(sf::Vertex{ { m_center.x - m_size.x * 0.5f, m_center.y - m_size.y * 0.5f } });
        m_drawInfo.spaceShipMainBodyVertexArray.append(sf::Vertex{ { m_center.x - m_size.x * 0.5f, m_center.y + m_size.y * 0.5f } });
        m_drawInfo.spaceShipMainBodyVertexArray.append(sf::Vertex{ { m_center.x + m_size.x * 0.5f, m_center.y + m_size.y * 0.5f } });
        m_drawInfo.spaceShipMainBodyVertexArray.append(sf::Vertex{ { m_center.x + m_size.x * 0.5f, m_center.y - m_size.y * 0.5f } });
        m_drawInfo.spaceShipMainBodyVertexArray[0].color = m_drawInfo.spaceShipMainBodyVertexArray[3].color = sf::Color::Red;
        m_drawInfo.spaceShipMainBodyVertexArray[1].color = m_drawInfo.spaceShipMainBodyVertexArray[2].color = sf::Color::Green;
    }
    void prepDraw() override {
        prepDrawSpaceShipMainBodyVertexArray();
        sf::Vector2f backMidPoint = (m_drawInfo.spaceShipMainBodyVertexArray[1].position + m_drawInfo.spaceShipMainBodyVertexArray[2].position) * 0.5f;
        float length = Math::norm(m_drawInfo.spaceShipMainBodyVertexArray[3].position - m_drawInfo.spaceShipMainBodyVertexArray[0].position);
        m_drawInfo.leftRocketVertexArray.clear();
        m_drawInfo.leftRocketVertexArray.setPrimitiveType(sf::Triangles);
        m_drawInfo.leftRocketVertexArray.append(sf::Vertex{ m_drawInfo.spaceShipMainBodyVertexArray[1].position });
        m_drawInfo.leftRocketVertexArray.append(sf::Vertex{ {m_drawInfo.spaceShipMainBodyVertexArray[1].position.x + length * 0.25f, m_drawInfo.spaceShipMainBodyVertexArray[1].position.y + length * 0.5f} });
        m_drawInfo.leftRocketVertexArray.append(sf::Vertex{ backMidPoint });
        m_drawInfo.leftRocketVertexArray[0].color = m_drawInfo.leftRocketVertexArray[1].color = m_drawInfo.leftRocketVertexArray[2].color = sf::Color::Green;
        m_drawInfo.rightRocketVertexArray.clear();
        m_drawInfo.rightRocketVertexArray.setPrimitiveType(sf::Triangles);
        m_drawInfo.rightRocketVertexArray.append(sf::Vertex{ m_drawInfo.spaceShipMainBodyVertexArray[2].position });
        m_drawInfo.rightRocketVertexArray.append(sf::Vertex{ {m_drawInfo.spaceShipMainBodyVertexArray[2].position.x - length * 0.25f, m_drawInfo.spaceShipMainBodyVertexArray[1].position.y + length * 0.5f} });
        m_drawInfo.rightRocketVertexArray.append(sf::Vertex{ backMidPoint });
        m_drawInfo.rightRocketVertexArray[0].color = m_drawInfo.rightRocketVertexArray[1].color = m_drawInfo.rightRocketVertexArray[2].color = sf::Color::Green;
        sf::Vector2f frontMidPoint = (m_drawInfo.spaceShipMainBodyVertexArray[0].position + m_drawInfo.spaceShipMainBodyVertexArray[3].position) * 0.5f;
        m_drawInfo.cockPitCircleShape.setPosition(frontMidPoint);
        m_drawInfo.cockPitCircleShape.setRadius(length * 0.5f);
        m_drawInfo.cockPitCircleShape.setOrigin(m_drawInfo.cockPitCircleShape.getRadius() * sf::Vector2f(1, 1));
        m_drawInfo.cockPitCircleShape.setFillColor(sf::Color::Red);
        m_drawInfo.gasCircleShapes.clear();
        if (m_movingForward) {
            sf::CircleShape y;
            y.setPosition(m_drawInfo.leftRocketVertexArray[1].position);
            y.setRadius(length * 0.1f);
            y.setOrigin(y.getRadius() * sf::Vector2f(1, 1));
            y.setFillColor(sf::Color::Yellow);
            m_drawInfo.gasCircleShapes.push_back(y);
            y.setPosition(m_drawInfo.rightRocketVertexArray[1].position);
            y.setRadius(length * 0.1f);
            y.setOrigin(y.getRadius() * sf::Vector2f(1, 1));
            y.setFillColor(sf::Color::Yellow);
            m_drawInfo.gasCircleShapes.push_back(y);
        }
        if (m_movingClockwise) {
            sf::CircleShape y;
            y.setPosition(m_drawInfo.leftRocketVertexArray[0].position);
            y.setRadius(length * 0.1f);
            y.setOrigin(y.getRadius() * sf::Vector2f(1, 1));
            y.setFillColor(sf::Color::Yellow);
            m_drawInfo.gasCircleShapes.push_back(y);
        }
        if (m_movingCounterClockwise) {
            sf::CircleShape y;
            y.setPosition(m_drawInfo.rightRocketVertexArray[0].position);
            y.setRadius(length * 0.1f);
            y.setOrigin(y.getRadius() * sf::Vector2f(1, 1));
            y.setFillColor(sf::Color::Yellow);
            m_drawInfo.gasCircleShapes.push_back(y);
        }
        for (int i = 0; i < 4; i++) {
            m_drawInfo.spaceShipMainBodyVertexArray[i].position = Math::rotateArountPoint(m_center, m_drawInfo.spaceShipMainBodyVertexArray[i].position, m_angle);
        }
        for (int i = 0; i < 3; i++) {
            m_drawInfo.leftRocketVertexArray[i].position = Math::rotateArountPoint(m_center, m_drawInfo.leftRocketVertexArray[i].position, m_angle);
            m_drawInfo.rightRocketVertexArray[i].position = Math::rotateArountPoint(m_center, m_drawInfo.rightRocketVertexArray[i].position, m_angle);
        }
        m_drawInfo.cockPitCircleShape.setPosition(Math::rotateArountPoint(m_center, m_drawInfo.cockPitCircleShape.getPosition(), m_angle));
        for (auto& circleShape : m_drawInfo.gasCircleShapes) {
            circleShape.setPosition(Math::rotateArountPoint(m_center, circleShape.getPosition(), m_angle));
        }
    }
    SpaceShip(const std::string& name, const sf::Vector2f& center, const sf::Vector2f size, float speed);
    SpaceShip(const SpaceShip& other);
    SpaceShip operator = (const SpaceShip& other);
    ~SpaceShip();
    sf::Vector2f getCenter() const;
    float getMass() const;
    void update(ObjectUpdateInfo m_drawInfo) override;
    void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const override;
    friend std::ostream& operator<<(std::ostream& os, const SpaceShip& SpaceShip);
};