#include "Cactus.h"



Cactus::Cactus()
{
    switch (type) {
    case 1: 
    CactusShape1 = new sf::Texture();
    sprite = LoadShape(
            CactusShape1,
            CACTUS1_HEIGHT, CACTUS1_WIDTH,
            cactus1);
    break;
    case 2:
        CactusShape2 = new sf::Texture();
        sprite = LoadShape(
            CactusShape2,
            CACTUS2_HEIGHT, CACTUS2_WIDTH,
            cactus2);
        break;
    case 3:
        CactusShape3 = new sf::Texture();
        sprite = LoadShape(
            CactusShape3,
            CACTUS3_HEIGHT, CACTUS3_WIDTH,
            cactus3);
        break;
    case 4:
        CactusShape4 = new sf::Texture();
        sprite = LoadShape(
            CactusShape4,
            CACTUS4_HEIGHT, CACTUS4_WIDTH,
            cactus4);
        break;
    default:
        CactusShape1 = new sf::Texture();
        sprite = LoadShape(
            CactusShape1,
            CACTUS1_HEIGHT, CACTUS1_WIDTH,
            cactus1);
        break;
    }
    sprite->scale(2, 2);
}

void Cactus::Init(int distance)
{
    sprite->setPosition(rand()%100 + WIDTH, 38);
}

void Cactus::Draw(sf::RenderWindow* window)
{
    window->draw(*sprite);
}

Cactus::~Cactus()
{
}
