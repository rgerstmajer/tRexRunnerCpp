//! Cactus.cpp
/*!
* Implementation of the Cactus class
*
* Created: 20.08.2018.
* Author : Robert Gerstmajer
*/
#include "Cactus.h"

Cactus::Cactus(float distance, int type)
{
  distance = (distance > 0) ? distance : -distance;
  switch (type) {
  case 1:
    m_cactusShape = new sf::Texture();
    m_sprite = LoadShape(
      m_cactusShape,
      CACTUS1_HEIGHT, CACTUS1_WIDTH,
      cactus1);
    m_sprite->setPosition(distance, HEIGHT - CACTUS1_HEIGHT * GAME_SCALE - 2);
    break;
  case 2:
    m_cactusShape = new sf::Texture();
    m_sprite = LoadShape(
      m_cactusShape,
      CACTUS2_HEIGHT, CACTUS2_WIDTH,
      cactus2);
    m_sprite->setPosition(distance, HEIGHT - CACTUS2_HEIGHT * GAME_SCALE - 2);
    break;
  case 3:
    m_cactusShape = new sf::Texture();
    m_sprite = LoadShape(
      m_cactusShape,
      CACTUS3_HEIGHT, CACTUS3_WIDTH,
      cactus3);
    m_sprite->setPosition(distance, HEIGHT - CACTUS3_HEIGHT * GAME_SCALE - 2);
    break;
  case 4:
    m_cactusShape = new sf::Texture();
    m_sprite = LoadShape(
      m_cactusShape,
      CACTUS4_HEIGHT, CACTUS4_WIDTH,
      cactus4);
    m_sprite->setPosition(distance, HEIGHT - CACTUS4_HEIGHT * GAME_SCALE - 2);
    break;
  default:
    m_cactusShape = new sf::Texture();
    m_sprite = LoadShape(
      m_cactusShape,
      CACTUS1_HEIGHT, CACTUS1_WIDTH,
      cactus1);
    m_sprite->setPosition(distance, HEIGHT - CACTUS1_HEIGHT * GAME_SCALE - 2);
    break;
  }
}

void Cactus::Update(float increment)
{
  m_sprite->move((increment < 0) ? increment : -increment , 0);
}

Cactus::~Cactus()
{
  DELETE_PTR(m_cactusShape);
  DELETE_PTR(m_sprite);
}
