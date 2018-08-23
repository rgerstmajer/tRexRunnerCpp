#include "TRex.h"
#include <Windows.h>

bool dropping = false;
TRex::TRex()
{
    State = RUNNING;
    sprite->setPosition(TREX_STARTING_POSITION_X, TREX_STARTING_POSITION_Y);
}

void TRex::Draw(sf::RenderWindow* window)
{
    
    window->draw(*sprite);
}

void TRex::Jump()
{
    State = (State == RUNNING) ? JUMPING : State;

    if (sprite->getPosition().y > TREX_MAX_HEIGHT && !dropping)
    {
        if ((sprite->getPosition().y - JUMPING_SPEED) < TREX_MAX_HEIGHT)
            sprite->setPosition(10, TREX_MAX_HEIGHT);
        if (sprite->getPosition().y == TREX_MAX_HEIGHT)
            dropping = true;
        else
            sprite->move(0, -JUMPING_SPEED);
    }
    else if (dropping)
    {
        if ((sprite->getPosition().y + GRAVITY) >= TREX_STARTING_POSITION_Y)
        {
            sprite->setPosition(TREX_STARTING_POSITION_X, TREX_STARTING_POSITION_Y);
            State = RUNNING;
            dropping = false;
        }
        else
            sprite->move(0, GRAVITY);
    }
}

void TRex::Duck()
{
    State = ( State == RUNNING ) ? DUCKING : State;
    if (State == DUCKING)
    {
        sprite->setRadius(5);
        sprite->setPosition(TREX_DUCKING_POSITION_X, TREX_DUCKING_POSITION_Y);
    }
}

void TRex::Run()
{
    State = ( State == JUMPING ) ? State : RUNNING;
    if (State == RUNNING)
    {
        sprite->setRadius(10);
        sprite->setPosition(TREX_STARTING_POSITION_X, TREX_STARTING_POSITION_Y);
    }
}

void TRex::Move(TRex::TRexStates newState) //Jumping or ducking
{
    if (State == DUCKING && newState == RUNNING)
    {
        sprite->setRadius(10);
        sprite->move(0, -5);
        State = RUNNING;
    }
    else
    {
        State = newState;
        if (State == JUMPING && (sprite->getPosition().y > TREX_MAX_HEIGHT))
        {
            if ((sprite->getPosition().y - JUMPING_SPEED) < TREX_MAX_HEIGHT)
                sprite->move(0, sprite->getPosition().y - TREX_MAX_HEIGHT - 1);
            else
                sprite->move(0, -JUMPING_SPEED);
            if (sprite->getPosition().y == TREX_MAX_HEIGHT)
                dropping = true;
        }
        else if (dropping)
        {
            if ((sprite->getPosition().y + GRAVITY) > 30)
            {
                sprite->move(0, sprite->getPosition().y + GRAVITY - 30);
                State = RUNNING;
            }
            else
                sprite->move(0, GRAVITY);
            
        }
        if (State == JUMPING && sprite->getPosition().y == 30)
        {
            State = RUNNING;
            dropping = false;
        }
        if (State == DUCKING)
        {
            sprite->setRadius(5);
            sprite->setPosition(10, 35);
        }
    }
    
}

void TRex::Move()
{
    
    
}


TRex::~TRex()
{

}
