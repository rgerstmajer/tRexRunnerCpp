#pragma once
#include <SFML\Graphics.hpp>
#include "Globals.h"
#include "Sprites.h"

class GameObject
{
protected:
    sf::Sprite* sprite;
    sf::Texture* shape;
public:
    GameObject();

    struct Position {
        uint8_t x;
        uint8_t y;
    };

    sf::Sprite* LoadShape(sf::Texture* texture, const int height, const int width, const unsigned char* shape);
    virtual void Draw(sf::RenderWindow* window);

    float getPositionX() { return sprite->getPosition().x; }
    float getPositionY() { return sprite->getPosition().y; }
    //float getRadius() { return sprite->getRadius(); }
    ~GameObject();
};
