#include "Pterodactyl.h"



Pterodactyl::Pterodactyl()
{

}


void Pterodactyl::Init() 
{
}

void Pterodactyl::Init(int distance)
{
    wingFlapCounter = 0;
    PterodactylShape1 = new sf::Texture();
    PterodactylShape2 = new sf::Texture();

    PterodactylSprite1 = LoadShape(PterodactylShape1, PTERODACTYL_HEIGHT, PTERODACTYL_WIDTH, pterodactyl1);
    PterodactylSprite2 = LoadShape(PterodactylShape2, PTERODACTYL_HEIGHT, PTERODACTYL_WIDTH, pterodactyl2);

    sprite = PterodactylSprite1;
    sprite->setPosition(distance, rand() % (HEIGHT-PTERODACTYL_HEIGHT*2-TREX_DUCKING_HEIGHT*2 - 2));
}

void Pterodactyl::Update()
{
    previousPositionX = sprite->getPosition().x;
    previousPositionY = sprite->getPosition().y;
    if (sprite == PterodactylSprite1 && wingFlapCounter >= 20)
    {
        wingFlapCounter = 0;
        sprite = PterodactylSprite2;
        sprite->setPosition(previousPositionX, previousPositionY);
    }
    else if (sprite == PterodactylSprite2 && wingFlapCounter >= 20)
    {
        wingFlapCounter = 0;
        sprite = PterodactylSprite1;
        sprite->setPosition(previousPositionX, previousPositionY);
    }
    wingFlapCounter++;
}

Pterodactyl::~Pterodactyl()
{
}
