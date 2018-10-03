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
  switch (type) {
  case 1:
    CactusShape = new sf::Texture();
    sprite = LoadShape(
      CactusShape,
      CACTUS1_HEIGHT, CACTUS1_WIDTH,
      cactus1);
    sprite->setPosition(distance, HEIGHT - CACTUS1_HEIGHT * GAME_SCALE - 2);
    break;
  case 2:
    CactusShape = new sf::Texture();
    sprite = LoadShape(
      CactusShape,
      CACTUS2_HEIGHT, CACTUS2_WIDTH,
      cactus2);
    sprite->setPosition(distance, HEIGHT - CACTUS2_HEIGHT * GAME_SCALE - 2);
    break;
  case 3:
    CactusShape = new sf::Texture();
    sprite = LoadShape(
      CactusShape,
      CACTUS3_HEIGHT, CACTUS3_WIDTH,
      cactus3);
    sprite->setPosition(distance, HEIGHT - CACTUS3_HEIGHT * GAME_SCALE - 2);
    break;
  case 4:
    CactusShape = new sf::Texture();
    sprite = LoadShape(
      CactusShape,
      CACTUS4_HEIGHT, CACTUS4_WIDTH,
      cactus4);
    sprite->setPosition(distance, HEIGHT - CACTUS4_HEIGHT * GAME_SCALE - 2);
    break;
  default:
    CactusShape = new sf::Texture();
    sprite = LoadShape(
      CactusShape,
      CACTUS1_HEIGHT, CACTUS1_WIDTH,
      cactus1);
    sprite->setPosition(distance, HEIGHT - CACTUS1_HEIGHT * GAME_SCALE - 2);
    break;
  }
}

void Cactus::Update(float increment)
{
  sprite->move(-increment, 0);
}

Cactus::~Cactus()
{
  delete CactusShape;
  CactusShape = NULL;
  delete sprite;
  sprite = NULL;
}