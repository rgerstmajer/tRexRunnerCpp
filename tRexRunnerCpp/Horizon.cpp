//! Horizon.cpp
/*!
* Implementation of the Horizon class
*
* Created: 20.08.2018.
* Author : Robert Gerstmajer
*/
#include "Horizon.h"

Horizon::Horizon(int type)
{
    switch (type)
    {
    case 1:
        bump = new sf::Texture();
        sprite = LoadShape(*bump, BUMP1_HEIGHT, BUMP1_WIDTH, bump1, true);
        sprite->setPosition(WIDTH / 3, HEIGHT - HORIZON_LINE_HEIGHT);
        break;
    case 2:
        bumps2 = new sf::Texture();
        sprite = LoadShape(*bumps2, BUMP2_HEIGHT, BUMP2_WIDTH, bump2, true);
        sprite->setPosition(2 * WIDTH / 3, HEIGHT - HORIZON_LINE_HEIGHT);
        break;
    default:
        break;
    }
}

void Horizon::Move(float increment) //Move details from right to left
{
    sprite->move(-increment, 0);
    if (sprite->getPosition().x < 0)
        sprite->move(WIDTH+rand()%WIDTH, 0);
}


Horizon::~Horizon()
{
    delete bump;
    delete bumps2;
}