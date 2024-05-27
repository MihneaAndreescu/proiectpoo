#pragma once

#include "GameObject.h"

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
};