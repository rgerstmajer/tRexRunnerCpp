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
    DeadShape = new sf::Texture();
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
        return;
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
    switch (State)
    {
        case JUMPING:
            Run();
            break;
        case RUNNING1:
            State = DUCKING1;
            Update();
            break;
        case RUNNING2:
            State = DUCKING2;
            Update();
            break;
        case DUCKING1:
            Update();
            break;
        case DUCKING2:
            Update();
            break;
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
        break;
    case RUNNING1:
        Update();
        break;
    case RUNNING2:
        Update();
        break;
    case DUCKING1:
        State = RUNNING1;
        Update();
        break;
    case DUCKING2:
        State = RUNNING1;
        Update();
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
    bool shouldStep = (stepCounter >= LIMB_CHANGE_COUNTER);
    switch (State)
    {
    case JUMPING:
        Jump();
        break;
    case RUNNING1:
        sprite = shouldStep ? RunningSprite2 : RunningSprite1;
        State = shouldStep ? RUNNING2 : State;
        sprite->setPosition(TREX_STARTING_POSITION_X, TREX_STARTING_POSITION_Y);
        break;
    case RUNNING2:
        sprite = shouldStep ? RunningSprite1 : RunningSprite2;
        State = shouldStep ? RUNNING1 : State;
        sprite->setPosition(TREX_STARTING_POSITION_X, TREX_STARTING_POSITION_Y);
        break;
    case DUCKING1:
        sprite = shouldStep ? DuckingSprite2 : DuckingSprite1;
        State = shouldStep ? DUCKING2 : State;
        sprite->setPosition(TREX_DUCKING_POSITION_X, TREX_DUCKING_POSITION_Y);
        break;
    case DUCKING2:
        sprite = shouldStep ? DuckingSprite1 : DuckingSprite2;
        State = shouldStep ? DUCKING1 : State;
        sprite->setPosition(TREX_DUCKING_POSITION_X, TREX_DUCKING_POSITION_Y);
        break;
    default:
        State = RUNNING1;
    }
    stepCounter = shouldStep ? 0 : stepCounter + 1;
}

TRex::~TRex()
{
    delete StandingShape;
    delete RunningShape1;
    delete RunningShape2;
    delete DuckingShape1;
    delete DuckingShape2;
    delete DeadShape;
    delete StandingSprite;
    delete RunningSprite1;
    delete RunningSprite2;
    delete DuckingSprite1;
    delete DuckingSprite2;
    delete DeadSprite;
}
