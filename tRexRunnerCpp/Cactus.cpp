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
    cactusShape = new sf::Texture();
    sprite = LoadShape(
      cactusShape,
      CACTUS1_HEIGHT, CACTUS1_WIDTH,
      cactus1);
    sprite->setPosition(distance, HEIGHT - CACTUS1_HEIGHT * GAME_SCALE - 2);
    break;
  case 2:
    cactusShape = new sf::Texture();
    sprite = LoadShape(
      cactusShape,
      CACTUS2_HEIGHT, CACTUS2_WIDTH,
      cactus2);
    sprite->setPosition(distance, HEIGHT - CACTUS2_HEIGHT * GAME_SCALE - 2);
    break;
  case 3:
    cactusShape = new sf::Texture();
    sprite = LoadShape(
      cactusShape,
      CACTUS3_HEIGHT, CACTUS3_WIDTH,
      cactus3);
    sprite->setPosition(distance, HEIGHT - CACTUS3_HEIGHT * GAME_SCALE - 2);
    break;
  case 4:
    cactusShape = new sf::Texture();
    sprite = LoadShape(
      cactusShape,
      CACTUS4_HEIGHT, CACTUS4_WIDTH,
      cactus4);
    sprite->setPosition(distance, HEIGHT - CACTUS4_HEIGHT * GAME_SCALE - 2);
    break;
  default:
    cactusShape = new sf::Texture();
    sprite = LoadShape(
      cactusShape,
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
  delete cactusShape;
  cactusShape = NULL;
  delete sprite;
  sprite = NULL;
}