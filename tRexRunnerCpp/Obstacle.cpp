#include "Obstacle.h"



Obstacle::Obstacle()
{

}


void Obstacle::Move(float increment)
{
    sprite->move(-(4 + increment), 0);
    if (sprite->getPosition().x < 0 - TREX_DUCKING_WIDTH);
    {
        Init();
    }
}

Obstacle::~Obstacle()
{

}
