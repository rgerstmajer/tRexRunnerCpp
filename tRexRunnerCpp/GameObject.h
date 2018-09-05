#pragma once
#include <SFML\Graphics.hpp>
#include "Globals.h"
#include "Sprites.h"

class GameObject
{
protected:
    sf::Texture* shape;
    sf::Sprite* LoadShape(sf::Texture* texture, const int height, const int width, const unsigned char* shape);
public:

    enum gameObjectType
    {
        TREX,
        OBSTACLE,
        HORIZON
    };

    void Draw(sf::RenderWindow* window);
    sf::Sprite* sprite;
    GameObject();

    struct Position {
        uint8_t x;
        uint8_t y;
    };


    bool Colliding(GameObject* obstacle);

    float getPositionX() { return sprite->getPosition().x; }
    float getPositionY() { return sprite->getPosition().y; }
    virtual void Init() = 0;
    ~GameObject();
};
