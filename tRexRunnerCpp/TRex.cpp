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
    State = RUNNING;
    sprite = StandingSprite;
    sprite->scale(2, 2);
    sprite->setPosition(TREX_STARTING_POSITION_X, TREX_STARTING_POSITION_Y);
}

//void TRex::Draw(sf::RenderWindow* window)
//{
//    window->draw(*sprite);
//}

void TRex::Jump()
{
    State = (State == RUNNING1) || (State == RUNNING2) ? JUMPING : State;

    if (sprite->getPosition().y > TREX_MAX_HEIGHT && !dropping)
    {
        if ((sprite->getPosition().y - JUMPING_SPEED) < TREX_MAX_HEIGHT)
        {
            sprite->setPosition(10, TREX_MAX_HEIGHT);
        }
        if (sprite->getPosition().y == TREX_MAX_HEIGHT)
            dropping = true;
        else
        {
            sprite->move(0, -JUMPING_SPEED);
        }
    }
    else if (dropping)
    {
        if ((sprite->getPosition().y + GRAVITY) >= TREX_STARTING_POSITION_Y)
        {
            sprite->setPosition(TREX_STARTING_POSITION_X, TREX_STARTING_POSITION_Y);
            State = RUNNING1;
            dropping = false;
        }
        else
        {
            sprite->move(0, GRAVITY);
        }
    }
}

void TRex::Duck()
{
    State = (State == RUNNING1) || (State == RUNNING2) ? DUCKING1 : State;
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
    State = ( State == JUMPING ) ? State : RUNNING1;
    if (State == RUNNING1)
    {
        sprite = RunningSprite1;
    }
    else if (State == RUNNING2)
    {
        sprite = RunningSprite2;
    }
}

void TRex::Move(TRex::TRexStates newState) //Jumping or ducking
{
    
}

void TRex::Move()
{
    
}


void TRex::LoadShapes(/*sf::Sprite sprite, sf::Texture, int height, int width*/)
{

    int row, column, position;
    for (register int i = 0; i < TREX_STANDING_HEIGHT * TREX_STANDING_WIDTH; i++)
    {
        row = i / (TREX_STANDING_WIDTH * 8);
        column = i % TREX_STANDING_WIDTH;
        position = 1 << (0 + ((i / TREX_STANDING_WIDTH) % 8));
        StandingOrRunningPixels[i * 4] = 255;
        StandingOrRunningPixels[i * 4 + 1] = 255;
        StandingOrRunningPixels[i * 4 + 2] = 255;
        StandingOrRunningPixels[i * 4 + 3] = ( trex_running1[ row + column + row * TREX_STANDING_WIDTH] & ( position ) ) ? 255 : 0;
    }
    StandingShape->create(TREX_STANDING_HEIGHT, TREX_STANDING_WIDTH);
    
    StandingShape->update(StandingOrRunningPixels);
    StandingSprite = new sf::Sprite(*StandingShape);
}


void TRex::Init()
{
    
}

TRex::~TRex()
{

}
