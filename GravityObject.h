#pragma once

#include "GameObject.h"
#include <memory>
#include "Math.h"
#include <cassert>

class GravityObject : public GameObject {
private:
    bool isAttracted;
    bool isAttracting;
public:
    GravityObject(bool isAttracted, bool isAttrracting) : isAttracted(isAttracted), isAttracting(isAttrracting) {

    }
    bool getIsAttracted() {
        return isAttracted;
    }
    bool getIsAttracting() {
        return isAttracting;
    }
    virtual void clearForces() = 0;
    virtual sf::Vector2f getCenter() const = 0;
    virtual float getMass() const = 0;
    virtual void applyForce(sf::Vector2f force) = 0;
    virtual void updateGravityObject(ObjectUpdateInfo m_drawInfo, const std::vector<std::shared_ptr<GameObject>>& allObjects = {}) = 0;
    std::vector<std::shared_ptr<GameObject>> update(ObjectUpdateInfo m_drawInfo, const std::vector<std::shared_ptr<GameObject>>& allObjects = {}) override {
        for (auto& obj : allObjects) {
            obj->dummy();
        }
        {
            for (auto& other : allObjects) {
                auto otherGravityObject = std::dynamic_pointer_cast<GravityObject>(other);
                if (otherGravityObject && otherGravityObject->getId() != this->getId()) {
                    sf::Vector2f dir = Math::normalize(otherGravityObject->getCenter() - this->getCenter());
                    float mag = this->getMass() * otherGravityObject->getMass() / Math::dot(dir, dir);
                    mag *= 0.01f;
                    this->applyForce(dir * mag);
                }
            }
        }
        {
            sf::Vector2f dir = this->getCenter();
            this->applyForce(-Math::normalize(dir) * 1.0f * Math::norm(dir) * Math::norm(dir));
        }
        updateGravityObject(m_drawInfo, allObjects);
        this->clearForces();
        return {};
    }
};