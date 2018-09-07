#include "Cactus.h"



Cactus::Cactus()
{
}

void Cactus::Init()
{
}

void Cactus::Init(int distance, int type)
{
    switch (type) {
    case 1:
        CactusShape1 = new sf::Texture();
        sprite = LoadShape(
            CactusShape1,
            CACTUS1_HEIGHT, CACTUS1_WIDTH,
            cactus1);
        sprite->setPosition(rand() % 100 + distance + WIDTH, HEIGHT - CACTUS1_HEIGHT * GAME_SCALE - 2);
        break;
    case 2:
        CactusShape2 = new sf::Texture();
        sprite = LoadShape(
            CactusShape2,
            CACTUS2_HEIGHT, CACTUS2_WIDTH,
            cactus2);
        sprite->setPosition(rand() % 100 + distance + WIDTH, HEIGHT - CACTUS2_HEIGHT * GAME_SCALE - 2);
        break;
    case 3:
        CactusShape3 = new sf::Texture();
        sprite = LoadShape(
            CactusShape3,
            CACTUS3_HEIGHT, CACTUS3_WIDTH,
            cactus3);
        sprite->setPosition(rand() % 100 + distance + WIDTH, HEIGHT - CACTUS3_HEIGHT * GAME_SCALE - 2);
        break;
    case 4:
        CactusShape4 = new sf::Texture();
        sprite = LoadShape(
            CactusShape4,
            CACTUS4_HEIGHT, CACTUS4_WIDTH,
            cactus4);
        sprite->setPosition(rand() % 100 + distance + WIDTH, HEIGHT - CACTUS4_HEIGHT * GAME_SCALE - 2);
        break;
    default:
        CactusShape1 = new sf::Texture();
        sprite = LoadShape(
            CactusShape1,
            CACTUS1_HEIGHT, CACTUS1_WIDTH,
            cactus1);
        sprite->setPosition(rand() % 100 + distance + WIDTH, HEIGHT - CACTUS1_HEIGHT * GAME_SCALE - 2);
        break;
    }
}

Cactus::~Cactus()
{
}