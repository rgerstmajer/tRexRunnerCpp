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
  m_standingShape = new sf::Texture();
  m_runningShape1 = new sf::Texture();
  m_runningShape2 = new sf::Texture();
  m_duckingShape1 = new sf::Texture();
  m_duckingShape2 = new sf::Texture();
  m_deadShape     = new sf::Texture();
  m_standingSprite = LoadShape(m_standingShape, TREX_STANDING_HEIGHT, TREX_STANDING_WIDTH, trex_standing_init);
  m_runningSprite1 = LoadShape(m_runningShape1, TREX_STANDING_HEIGHT, TREX_STANDING_WIDTH, trex_running1);
  m_runningSprite2 = LoadShape(m_runningShape2, TREX_STANDING_HEIGHT, TREX_STANDING_WIDTH, trex_running2);
  m_duckingSprite1 = LoadShape(m_duckingShape1, TREX_DUCKING_HEIGHT, TREX_DUCKING_WIDTH, trex_ducking1);
  m_duckingSprite2 = LoadShape(m_duckingShape2, TREX_DUCKING_HEIGHT, TREX_DUCKING_WIDTH, trex_ducking2);
  m_deadSprite     = LoadShape(m_deadShape, TREX_STANDING_HEIGHT, TREX_STANDING_WIDTH, trex_dead);
  m_state = STANDING;
  m_sprite = m_standingSprite;
  m_sprite->setPosition(TREX_STARTING_POSITION_X, TREX_STARTING_POSITION_Y);
}

void TRex::Jump()
{
  m_state = (m_state == STANDING) || (m_state == RUNNING1) || (m_state == RUNNING2) ? JUMPING : m_state;
  if (m_state == DUCKING1 || m_state == DUCKING2)
  {
    return;
  }
  else if (m_sprite->getPosition().y > TREX_MAX_HEIGHT && !m_dropping)
  {
    if ((m_sprite->getPosition().y - m_JumpingSpeed) <= TREX_MAX_HEIGHT)
    {
      m_sprite->setPosition(TREX_STARTING_POSITION_X, TREX_MAX_HEIGHT);
      m_dropping = true;
    }
    else
    {
      m_sprite->move(0, -m_JumpingSpeed);
    }
  }
  else if (m_dropping)
  {
    if ((m_sprite->getPosition().y + m_Gravity) >= TREX_STARTING_POSITION_Y)
    {
      m_sprite->setPosition(TREX_STARTING_POSITION_X, TREX_STARTING_POSITION_Y);
      m_state = RUNNING1;
      m_dropping = false;
    }
    else
    {
      m_sprite->move(0, m_Gravity);
    }
  }
}

void TRex::Duck()
{
  switch (m_state)
  {
    case JUMPING:
      Run();
      break;
    case RUNNING1:
      m_state = DUCKING1;
      Update();
      break;
    case RUNNING2:
      m_state = DUCKING2;
      Update();
      break;
    case DUCKING1:
      Update();
      break;
    case DUCKING2:
      Update();
      break;
    default:
      m_state = DUCKING1;
      Update();
      break;
  }
}

void TRex::Run()
{
  switch (m_state)
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
    m_state = RUNNING1;
    Update();
    break;
  case DUCKING2:
    m_state = RUNNING1;
    Update();
    break;
  default:
    break;
  }
}

void TRex::Crash()
{
  m_state = CRASHED;
  m_sprite = m_deadSprite;
  m_sprite->setPosition(TREX_STARTING_POSITION_X, TREX_STARTING_POSITION_Y);
}

void TRex::Update()
{
  bool shouldStep = (m_stepCounter >= LIMB_CHANGE_COUNTER);
  switch (m_state)
  {
  case JUMPING:
    Jump();
    break;
  case RUNNING1:
    m_sprite = shouldStep ? m_runningSprite2 : m_runningSprite1;
    m_state = shouldStep ? RUNNING2 : m_state;
    m_sprite->setPosition(TREX_STARTING_POSITION_X, TREX_STARTING_POSITION_Y);
    break;
  case RUNNING2:
    m_sprite = shouldStep ? m_runningSprite1 : m_runningSprite2;
    m_state = shouldStep ? RUNNING1 : m_state;
    m_sprite->setPosition(TREX_STARTING_POSITION_X, TREX_STARTING_POSITION_Y);
    break;
  case DUCKING1:
    m_sprite = shouldStep ? m_duckingSprite2 : m_duckingSprite1;
    m_state = shouldStep ? DUCKING2 : m_state;
    m_sprite->setPosition(TREX_DUCKING_POSITION_X, TREX_DUCKING_POSITION_Y);
    break;
  case DUCKING2:
    m_sprite = shouldStep ? m_duckingSprite1 : m_duckingSprite2;
    m_state = shouldStep ? DUCKING1 : m_state;
    m_sprite->setPosition(TREX_DUCKING_POSITION_X, TREX_DUCKING_POSITION_Y);
    break;
  default:
    m_state = RUNNING1;
  }
  m_stepCounter = shouldStep ? 1 : m_stepCounter + 1;
}

TRex::~TRex()
{
  DELETE_PTR(m_standingShape);
  DELETE_PTR(m_runningShape1);
  DELETE_PTR(m_runningShape2);
  DELETE_PTR(m_duckingShape1);
  DELETE_PTR(m_duckingShape2);
  DELETE_PTR(m_deadShape);
  DELETE_PTR(m_standingSprite);
  DELETE_PTR(m_runningSprite1);
  DELETE_PTR(m_runningSprite2);
  DELETE_PTR(m_duckingSprite1);
  DELETE_PTR(m_duckingSprite2);
  DELETE_PTR(m_deadSprite);
}
