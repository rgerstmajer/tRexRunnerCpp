#include "Cactus.h"



Cactus::Cactus()
{
    sprite->setRadius( 7 );
}

void Cactus::Init()
{
    
    sprite->setPosition(rand()%100 + 300, 38);
}

void Cactus::Move() //Right to left
{
    sprite->move(-GAME_SPEED, 0);
    if (sprite->getPosition().x < (0 - sprite->getRadius() * 2))
        Init();
}

void Cactus::Draw(sf::RenderWindow* window)
{
    window->draw(*sprite);
}

Cactus::~Cactus()
{
}
