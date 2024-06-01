#include <SFML/Graphics.hpp>
#include "DuneExceptions.h"

class Heart : public sf::Drawable {
private:
    sf::CircleShape m_topLeftCircleShape;
    sf::CircleShape m_topRightCircleShape;
    sf::ConvexShape m_bottomPartOfHeart;
public:
    Heart(float x, float y, float size);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};