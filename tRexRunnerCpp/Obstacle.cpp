#include "Obstacle.h"



Obstacle::Obstacle()
{

}


void Obstacle::Move(float increment)
{
    try
    {
        sprite->move(-(4 + increment), 0);
    }
    catch (...) {};
}

Obstacle::~Obstacle()
{

}
