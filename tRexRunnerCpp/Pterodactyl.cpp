//! Pterodactyl.cpp
/*!
* Implementation of the Pterodactyl class
*
* Created: 20.08.2018.
* Author : Robert Gerstmajer
*/
#include "Pterodactyl.h"

Pterodactyl::Pterodactyl(float distance)
{
  m_wingFlapCounter = 0;
  m_pterodactylShape1 = new sf::Texture();
  m_pterodactylShape2 = new sf::Texture();
  if (m_pterodactylShape1 == NULL || m_pterodactylShape2 == NULL)
  {
    throw "Could not create texture for Pterodactyl sprite";
  }

  m_pterodactylSprite1 = LoadShape(m_pterodactylShape1, PTERODACTYL_HEIGHT, PTERODACTYL_WIDTH, pterodactyl1);
  m_pterodactylSprite2 = LoadShape(m_pterodactylShape2, PTERODACTYL_HEIGHT, PTERODACTYL_WIDTH, pterodactyl2);
  if (m_pterodactylSprite1 == NULL || m_pterodactylSprite2 == NULL)
  {
    throw "Could not create Pterodactyl sprite";
  }
  m_sprite = m_pterodactylSprite1;
  m_sprite->setPosition(distance, rand() % (HEIGHT - PTERODACTYL_HEIGHT * 2 - TREX_DUCKING_HEIGHT * 2 - 2));
}

void Pterodactyl::Update(float increment)
{
  m_previousPositionX = m_sprite->getPosition().x;
  m_previousPositionY = m_sprite->getPosition().y;
  m_sprite->move(-increment, 0);
  if (m_sprite == m_pterodactylSprite1 && m_wingFlapCounter >= LIMB_CHANGE_COUNTER)
  {
    m_wingFlapCounter = 0;
    m_sprite = m_pterodactylSprite2;
    m_sprite->setPosition(m_previousPositionX, m_previousPositionY);
  }
  else if (m_sprite == m_pterodactylSprite2 && m_wingFlapCounter >= LIMB_CHANGE_COUNTER)
  {
    m_wingFlapCounter = 0;
    m_sprite = m_pterodactylSprite1;
    m_sprite->setPosition(m_previousPositionX, m_previousPositionY);
  }
  m_wingFlapCounter++;
}

Pterodactyl::~Pterodactyl()
{
  DELETE_PTR(m_pterodactylShape1);
  DELETE_PTR(m_pterodactylShape2);
  DELETE_PTR(m_pterodactylSprite1);
  DELETE_PTR(m_pterodactylSprite2);
}
