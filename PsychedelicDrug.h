#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "GravityObject.h"
#include "Shroom.h"

class PsychedelicDrug : public GameObject {
private:
    std::string m_name;
    sf::Vector2f m_center;
    Shroom m_shroom;
public:
    void prepDraw() override;
    explicit PsychedelicDrug(const std::string& name);
    PsychedelicDrug(const PsychedelicDrug& other);
    sf::Vector2f getCenter() const;
    PsychedelicDrug operator = (const PsychedelicDrug& other);
    ~PsychedelicDrug();
    void update(ObjectUpdateInfo m_updateInfo) override;
    void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const override;
    friend std::ostream& operator<<(std::ostream& os, const PsychedelicDrug& planet);
    sf::CircleShape getCap();
};