#pragma once

#include "GameObject.h"

class GravityObject : public GameObject {
public:
    virtual void clearForces() = 0;
    virtual sf::Vector2f getCenter() const = 0;
    virtual float getMass() const = 0;
    virtual void applyForce(sf::Vector2f force) = 0;
};