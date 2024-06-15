#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "GravityObject.h"
#include "Heart.h"

class HeartObject : public GameObject {
private:
    std::string m_name;
    sf::Vector2f m_center;
    Heart m_heart;
    float m_time;
public:
    explicit HeartObject(sf::Vector2f center, const std::string& name);
    HeartObject(const HeartObject& other);
    sf::CircleShape getCircle() const;
    bool isDead() const;
    sf::Vector2f getCenter() const;
    void update(ObjectUpdateInfo m_updateInfo, const std::vector<std::shared_ptr<GameObject>>& allObjects) override;
    void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const override;
    void prepDraw() override;
    HeartObject& operator=(const HeartObject& other);
    friend std::ostream& operator<<(std::ostream& os, const HeartObject& planet);
};
