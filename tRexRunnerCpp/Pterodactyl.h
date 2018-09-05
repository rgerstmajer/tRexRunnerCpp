#pragma once
#include "Obstacle.h"
class Pterodactyl :
    public Obstacle
{
public:

    Pterodactyl();

    sf::Texture* PterodactylShape1;
    sf::Sprite* PterodactylSprite1;

    sf::Texture* PterodactylShape2;
    sf::Sprite* PterodactylSprite2;

    void Init();

    ~Pterodactyl();
};

