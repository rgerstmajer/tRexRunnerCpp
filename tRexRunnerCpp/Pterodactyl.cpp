#include "Pterodactyl.h"



Pterodactyl::Pterodactyl()
{
    PterodactylShape1 = new sf::Texture();
    PterodactylShape2 = new sf::Texture();

    PterodactylSprite1 = LoadShape(PterodactylShape1, PTERODACTYL_HEIGHT, PTERODACTYL_WIDTH, pterodactyl1);
    PterodactylSprite2 = LoadShape(PterodactylShape2, PTERODACTYL_HEIGHT, PTERODACTYL_WIDTH, pterodactyl2);

    sprite = PterodactylSprite1;
    sprite->scale(2, 2);
}


void Pterodactyl::Init() // Initialize at new time
{
    sprite->setPosition(rand() % 100 + 350, 10);
}

Pterodactyl::~Pterodactyl()
{
}
