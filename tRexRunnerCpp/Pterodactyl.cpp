#include "Pterodactyl.h"



Pterodactyl::Pterodactyl()
{

}


void Pterodactyl::Init() 
{
    wingFlapCounter = 0;
    PterodactylShape1 = new sf::Texture();
    PterodactylShape2 = new sf::Texture();

    PterodactylSprite1 = LoadShape(PterodactylShape1, PTERODACTYL_HEIGHT, PTERODACTYL_WIDTH, pterodactyl1);
    PterodactylSprite2 = LoadShape(PterodactylShape2, PTERODACTYL_HEIGHT, PTERODACTYL_WIDTH, pterodactyl2);

    sprite = PterodactylSprite1;
}

void Pterodactyl::Init(int distance)
{
    sprite->setPosition(distance, rand() % HEIGHT-TREX_STANDING_HEIGHT - 1);
}

void Pterodactyl::Update()
{
    if (sprite == PterodactylSprite1 && wingFlapCounter > 20)
    {
        wingFlapCounter = 0;
        sprite = PterodactylSprite2;
    }
    else if (sprite == PterodactylSprite2 && wingFlapCounter > 20)
    {
        wingFlapCounter = 0;
        sprite = PterodactylSprite2;
    }
    wingFlapCounter++;
}

Pterodactyl::~Pterodactyl()
{
}
