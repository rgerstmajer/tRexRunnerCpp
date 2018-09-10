#pragma once
#include <SFML\Graphics.hpp>
#include "Globals.h"

class GameObject
{
  public:
    enum gameObjectType
    {
        TREX,
        PTERODACTYL,
        CACTUS,
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

    float GetPositionX() { return sprite->getPosition().x; }
    float GetPositionY() { return sprite->getPosition().y; }
    virtual void Init() = 0;
    ~GameObject();
protected:
    sf::Texture* shape;
    sf::Sprite* LoadShape(sf::Texture* texture, const int height, const int width, const unsigned char* shape, bool isBump = false);
};
