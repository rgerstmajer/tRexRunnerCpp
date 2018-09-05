#include "Cactus.h"



Cactus::Cactus()
{
    CactusShape1 = new sf::Texture();
    CactusShape2 = new sf::Texture();
    CactusShape3 = new sf::Texture();
    CactusShape4 = new sf::Texture();

    CactusSprite1 = LoadShape(CactusShape1, CACTUS1_HEIGHT, CACTUS1_WIDTH, cactus1);
    CactusSprite2 = LoadShape(CactusShape2, CACTUS2_HEIGHT, CACTUS2_WIDTH, cactus2);
    CactusSprite3 = LoadShape(CactusShape3, CACTUS3_HEIGHT, CACTUS3_WIDTH, cactus3);
    CactusSprite4 = LoadShape(CactusShape4, CACTUS4_HEIGHT, CACTUS4_WIDTH, cactus4);

    sprite = CactusSprite1;
    sprite->scale(2, 2);
}

void Cactus::Init()
{
    switch (rand()%4)
    {
    case 0:
        sprite = CactusSprite1;
        break;
    case 1:
        sprite = CactusSprite2;
        break;
    case 2:
        sprite = CactusSprite3;
        break;
    case 3:
        sprite = CactusSprite4;
        break;
    default:
        break;
    }
    sprite->setPosition(rand()%100 + WIDTH, 38);
}

void Cactus::Draw(sf::RenderWindow* window)
{
    window->draw(*sprite);
}

Cactus::~Cactus()
{
}
