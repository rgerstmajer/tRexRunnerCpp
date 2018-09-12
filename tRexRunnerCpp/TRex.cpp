//! TRex.cpp
/*!
* Implementation of the TRex class
*
* Created: 20.08.2018.
* Author : Robert Gerstmajer
*/
#include "TRex.h"
#include <Windows.h>

bool dropping = false;
TRex::TRex(float jumpingSpeed, float gravity)
{
    m_JumpingSpeed = jumpingSpeed;
    m_Gravity = gravity;
    StandingShape = new sf::Texture();
    RunningShape1 = new sf::Texture();
    RunningShape2 = new sf::Texture();
    DuckingShape1 = new sf::Texture();
    DuckingShape2 = new sf::Texture();
    DeadShape     = new sf::Texture();
    StandingSprite = LoadShape(StandingShape, TREX_STANDING_HEIGHT, TREX_STANDING_WIDTH, trex_standing_init);
    RunningSprite1 = LoadShape(RunningShape1, TREX_STANDING_HEIGHT, TREX_STANDING_WIDTH, trex_running1);
    RunningSprite2 = LoadShape(RunningShape2, TREX_STANDING_HEIGHT, TREX_STANDING_WIDTH, trex_running2);
    DuckingSprite1 = LoadShape(DuckingShape1, TREX_DUCKING_HEIGHT, TREX_DUCKING_WIDTH, trex_ducking1);
    DuckingSprite2 = LoadShape(DuckingShape2, TREX_DUCKING_HEIGHT, TREX_DUCKING_WIDTH, trex_ducking2);
    DeadSprite     = LoadShape(DeadShape, TREX_STANDING_HEIGHT, TREX_STANDING_WIDTH, trex_dead);
    State = STANDING;
    sprite = StandingSprite;
    sprite->setPosition(TREX_STARTING_POSITION_X, TREX_STARTING_POSITION_Y);
}

void TRex::Jump()
{
    State = (State == STANDING) || (State == RUNNING1) || (State == RUNNING2) ? JUMPING : State;
    if (State == DUCKING1 || State == DUCKING2)
    {
        Duck();
    }
    else if (sprite->getPosition().y > TREX_MAX_HEIGHT && !dropping)
    {
        if ((sprite->getPosition().y - m_JumpingSpeed) <= TREX_MAX_HEIGHT)
        {
            sprite->setPosition(TREX_STARTING_POSITION_X, TREX_MAX_HEIGHT);
            dropping = true;
        }
        else
        {
            sprite->move(0, -m_JumpingSpeed);
        }
    }
    else if (dropping)
    {
        if ((sprite->getPosition().y + m_Gravity) >= TREX_STARTING_POSITION_Y)
        {
            sprite->setPosition(TREX_STARTING_POSITION_X, TREX_STARTING_POSITION_Y);
            State = RUNNING1;
            dropping = false;
        }
        else
        {
            sprite->move(0, m_Gravity);
        }
    }
}

void TRex::Duck()
{
    State = (State==JUMPING) ? State : DUCKING1;
    if (State == JUMPING)
    {
        Jump();
    }
    else if (State == DUCKING1)
    {
        sprite = DuckingSprite1;
        sprite->setPosition(TREX_DUCKING_POSITION_X, TREX_DUCKING_POSITION_Y);
    }
    else if (State == DUCKING2)
    {
        sprite = DuckingSprite2;
        sprite->setPosition(TREX_DUCKING_POSITION_X, TREX_DUCKING_POSITION_Y);
    }
}

void TRex::Run()
{
    switch (State)
    {
    case JUMPING:
        Jump();
        break;
    case STANDING:
        Update();
    case RUNNING1:
        Update();
        break;
    case RUNNING2:
        Update();
        break;
    case DUCKING1:
        State = RUNNING1;
        break;
    case DUCKING2:
        State = RUNNING1;
        break;
    default:
        break;
    }
}

void TRex::Crash()
{
    State = CRASHED;
    sprite = DeadSprite;
    sprite->setPosition(TREX_STARTING_POSITION_X, TREX_STARTING_POSITION_Y);
}

void TRex::Update()
{
    stepCounter++;
    if (stepCounter >= 15)
    {
        switch (State)
        {
        case JUMPING:
            break;
        case RUNNING1:
            sprite = RunningSprite2;
            sprite->setPosition(TREX_STARTING_POSITION_X, TREX_STARTING_POSITION_Y);
            State = RUNNING2;
            break;
        case RUNNING2:
            sprite = RunningSprite1;
            sprite->setPosition(TREX_STARTING_POSITION_X, TREX_STARTING_POSITION_Y);
            State = RUNNING1;
            break;
        case DUCKING1:
            sprite = DuckingSprite2;
            sprite->setPosition(TREX_DUCKING_POSITION_X, TREX_DUCKING_POSITION_Y);
            State = DUCKING2;
            break;
        case DUCKING2:
            sprite = DuckingSprite1;
            sprite->setPosition(TREX_DUCKING_POSITION_X, TREX_DUCKING_POSITION_Y);
            State = DUCKING1;
            break;
        default:
            State = RUNNING1;
        }
        stepCounter = 0;
    }
}

TRex::~TRex()
{

}
