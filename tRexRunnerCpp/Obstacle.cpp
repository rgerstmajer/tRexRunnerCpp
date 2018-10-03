//! Obstacle.cpp
/*!
* Implementation of the Obstacle class
*
* Created: 20.08.2018.
* Author : Robert Gerstmajer
*/
#include "Obstacle.h"

Obstacle::Obstacle()
{

}


void Obstacle::Update(float increment)
{
  sprite->move(-increment, 0);
}

Obstacle::~Obstacle()
{

}
