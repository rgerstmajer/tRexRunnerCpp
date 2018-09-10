#include "Obstacle.h"



Obstacle::Obstacle()
{

}


void Obstacle::Move(float increment)
{
    sprite->move(-increment, 0);
}

Obstacle::~Obstacle()
{

}
