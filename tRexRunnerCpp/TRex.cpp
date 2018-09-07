#include "TRex.h"
#include <Windows.h>

bool dropping = false;
TRex::TRex()
{
    StandingShape = new sf::Texture();
    RunningShape1 = new sf::Texture();
    RunningShape2 = new sf::Texture();
    DuckingShape1 = new sf::Texture();
    DuckingShape2 = new sf::Texture();
    StandingSprite = LoadShape(StandingShape, TREX_STANDING_HEIGHT, TREX_STANDING_WIDTH, trex_standing_init);
    RunningSprite1 = LoadShape(RunningShape1, TREX_STANDING_HEIGHT, TREX_STANDING_WIDTH, trex_running1);
    RunningSprite2 = LoadShape(RunningShape2, TREX_STANDING_HEIGHT, TREX_STANDING_WIDTH, trex_running2);
    DuckingSprite1 = LoadShape(DuckingShape1, TREX_DUCKING_HEIGHT, TREX_DUCKING_WIDTH, trex_ducking1);
    DuckingSprite2 = LoadShape(DuckingShape2, TREX_DUCKING_HEIGHT, TREX_DUCKING_WIDTH, trex_ducking2);
    State = STANDING;
    sprite->setPosition(TREX_STARTING_POSITION_X, TREX_STARTING_POSITION_Y);
}

void TRex::Jump()
{
    State = (State == RUNNING1) || (State == RUNNING2) ? JUMPING : State;

    if (sprite->getPosition().y > TREX_MAX_HEIGHT && !dropping)
    {
        if ((sprite->getPosition().y - 2) <= TREX_MAX_HEIGHT)
        {
            sprite->setPosition(10, TREX_MAX_HEIGHT);
            dropping = true;
        }
        else
        {
            sprite->move(0, -2);
        }
    }
    else if (dropping)
    {
        if ((sprite->getPosition().y + 1) >= TREX_STARTING_POSITION_Y)
        {
            sprite->setPosition(TREX_STARTING_POSITION_X, TREX_STARTING_POSITION_Y);
            State = RUNNING1;
            dropping = false;
        }
        else
        {
            sprite->move(0, 1);
        }
    }
}

void TRex::Duck()
{
    State = (State==JUMPING) ? State : DUCKING1;
    if (State == DUCKING1)
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
    State = (State == JUMPING) ? State : RUNNING1;
    if (State == RUNNING1)
    {
        sprite = RunningSprite1;
        sprite->setPosition(TREX_STARTING_POSITION_X, TREX_STARTING_POSITION_Y);
    }
    else if (State == RUNNING2)
    {
        sprite = RunningSprite2;
        sprite->setPosition(TREX_STARTING_POSITION_X, TREX_STARTING_POSITION_Y);
    }
}

void TRex::Update()
{
    if (State == RUNNING1 && stepCounter < 15)
    {
        stepCounter++;
        sprite = RunningSprite1;
        sprite->setPosition(TREX_STARTING_POSITION_X, TREX_STARTING_POSITION_Y);
        State = RUNNING2;
    }
    else if (State == RUNNING2 && stepCounter < 15)
    {
        stepCounter++;
        sprite = RunningSprite2;
        sprite->setPosition(TREX_STARTING_POSITION_X, TREX_STARTING_POSITION_Y);
        State = RUNNING1;
    }
    else if (State == DUCKING1 && stepCounter < 15)
    {
        stepCounter++;
        sprite = DuckingSprite1;
        sprite->setPosition(TREX_STARTING_POSITION_X, TREX_DUCKING_POSITION_Y);
        State = DUCKING2;
    }
    else if (State == DUCKING2 && stepCounter < 15)
    {
        stepCounter++;
        sprite = DuckingSprite2;
        sprite->setPosition(TREX_STARTING_POSITION_X, TREX_DUCKING_POSITION_Y);
        State = DUCKING1;
    }
    else if (State == JUMPING)
    {
        Jump();
    }
    else
    {
        stepCounter = 0;
    }
}

void TRex::Init()
{

}

TRex::~TRex()
{

}
