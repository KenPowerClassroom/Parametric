#include "Viewport.h"

sf::Vector2f Viewport::screenSpace(sf::Vector2f p) {

    float x = xOrigin + width * p.x;
    float y = height - (yOrigin + height * p.y);

    return sf::Vector2f(x, y);

}