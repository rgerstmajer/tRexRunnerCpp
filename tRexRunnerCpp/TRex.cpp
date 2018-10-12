//! TRex.cpp
/*!
* Implementation of the TRex class
*
* Created: 20.08.2018.
* Author : Robert Gerstmajer
*/
#include "TRex.h"
#include <Windows.h>


TRex::TRex(float jumpingSpeed, float gravity)
{
  m_JumpingSpeed = (jumpingSpeed > 0) ? jumpingSpeed : -jumpingSpeed;
  m_Gravity = (gravity > 0) ? gravity : -gravity;
  standingShape = new sf::Texture();
  runningShape1 = new sf::Texture();
  runningShape2 = new sf::Texture();
  duckingShape1 = new sf::Texture();
  duckingShape2 = new sf::Texture();
  deadShape = new sf::Texture();
  standingSprite = LoadShape(standingShape, TREX_STANDING_HEIGHT, TREX_STANDING_WIDTH, trex_standing_init);
  runningSprite1 = LoadShape(runningShape1, TREX_STANDING_HEIGHT, TREX_STANDING_WIDTH, trex_running1);
  runningSprite2 = LoadShape(runningShape2, TREX_STANDING_HEIGHT, TREX_STANDING_WIDTH, trex_running2);
  duckingSprite1 = LoadShape(duckingShape1, TREX_DUCKING_HEIGHT, TREX_DUCKING_WIDTH, trex_ducking1);
  duckingSprite2 = LoadShape(duckingShape2, TREX_DUCKING_HEIGHT, TREX_DUCKING_WIDTH, trex_ducking2);
  deadSprite   = LoadShape(deadShape, TREX_STANDING_HEIGHT, TREX_STANDING_WIDTH, trex_dead);
  state = STANDING;
  sprite = standingSprite;
  sprite->setPosition(TREX_STARTING_POSITION_X, TREX_STARTING_POSITION_Y);
}

void TRex::Jump()
{
  state = (state == STANDING) || (state == RUNNING1) || (state == RUNNING2) ? JUMPING : state;
  if (state == DUCKING1 || state == DUCKING2)
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
      state = RUNNING1;
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
  switch (state)
  {
    case JUMPING:
      Run();
      break;
    case RUNNING1:
      state = DUCKING1;
      Update();
      break;
    case RUNNING2:
      state = DUCKING2;
      Update();
      break;
    case DUCKING1:
      Update();
      break;
    case DUCKING2:
      Update();
      break;
    default:
      state = DUCKING1;
      Update();
      break;
  }
}

void TRex::Run()
{
  switch (state)
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
    state = RUNNING1;
    Update();
    break;
  case DUCKING2:
    state = RUNNING1;
    Update();
    break;
  default:
    break;
  }
}

void TRex::Crash()
{
  state = CRASHED;
  sprite = deadSprite;
  sprite->setPosition(TREX_STARTING_POSITION_X, TREX_STARTING_POSITION_Y);
}

void TRex::Update()
{
  bool shouldStep = (stepCounter >= LIMB_CHANGE_COUNTER);
  switch (state)
  {
  case JUMPING:
    Jump();
    break;
  case RUNNING1:
    sprite = shouldStep ? runningSprite2 : runningSprite1;
    state = shouldStep ? RUNNING2 : state;
    sprite->setPosition(TREX_STARTING_POSITION_X, TREX_STARTING_POSITION_Y);
    break;
  case RUNNING2:
    sprite = shouldStep ? runningSprite1 : runningSprite2;
    state = shouldStep ? RUNNING1 : state;
    sprite->setPosition(TREX_STARTING_POSITION_X, TREX_STARTING_POSITION_Y);
    break;
  case DUCKING1:
    sprite = shouldStep ? duckingSprite2 : duckingSprite1;
    state = shouldStep ? DUCKING2 : state;
    sprite->setPosition(TREX_DUCKING_POSITION_X, TREX_DUCKING_POSITION_Y);
    break;
  case DUCKING2:
    sprite = shouldStep ? duckingSprite1 : duckingSprite2;
    state = shouldStep ? DUCKING1 : state;
    sprite->setPosition(TREX_DUCKING_POSITION_X, TREX_DUCKING_POSITION_Y);
    break;
  default:
    state = RUNNING1;
  }
  stepCounter = shouldStep ? 1 : stepCounter + 1;
}

TRex::~TRex()
{
  delete(standingShape);
  delete(runningShape1);
  delete(runningShape2);
  delete(duckingShape1);
  delete(duckingShape2);
  delete(deadShape);
  delete(standingSprite);
  delete(runningSprite1);
  delete(runningSprite2);
  delete(duckingSprite1);
  delete(duckingSprite2);
  delete(deadSprite);
}
