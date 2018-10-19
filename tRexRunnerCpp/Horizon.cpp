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
    m_bump = new sf::Texture();
    m_sprite = LoadShape(m_bump, BUMP1_HEIGHT, BUMP1_WIDTH, bump1, true);
    m_sprite->setPosition(WIDTH / 3, HEIGHT - HORIZON_LINE_HEIGHT);
    break;
  case 2:
    m_bump = new sf::Texture();
    m_sprite = LoadShape(m_bump, BUMP2_HEIGHT, BUMP2_WIDTH, bump2, true);
    m_sprite->setPosition(2 * WIDTH / 3, HEIGHT - HORIZON_LINE_HEIGHT);
    break;
  default:
    m_bump = new sf::Texture();
    m_sprite = LoadShape(m_bump, BUMP1_HEIGHT, BUMP1_WIDTH, bump1, true);
    m_sprite->setPosition(WIDTH / 3, HEIGHT - HORIZON_LINE_HEIGHT);
    break;
  }
}

void Horizon::Move(float increment) //Move bumps from right to left
{
  increment = (increment < 0) ? -increment : increment;
  m_sprite->move(-increment, 0);
  if (m_sprite->getPosition().x < 0)
    m_sprite->move(WIDTH + rand() % WIDTH, 0);
}


Horizon::~Horizon()
{
  DELETE_PTR(m_sprite);
  DELETE_PTR(m_bump);
}
