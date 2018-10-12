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
  wingFlapCounter = 0;
  pterodactylShape1 = new sf::Texture();
  pterodactylShape2 = new sf::Texture();
  if (pterodactylShape1 == NULL || pterodactylShape2 == NULL)
  {
    throw "Could not create texture for Pterodactyl sprite";
  }

  pterodactylSprite1 = LoadShape(pterodactylShape1, PTERODACTYL_HEIGHT, PTERODACTYL_WIDTH, pterodactyl1);
  pterodactylSprite2 = LoadShape(pterodactylShape2, PTERODACTYL_HEIGHT, PTERODACTYL_WIDTH, pterodactyl2);
  if (pterodactylSprite1 == NULL || pterodactylSprite2 == NULL)
  {
    throw "Could not create Pterodactyl sprite";
  }
  sprite = pterodactylSprite1;
  sprite->setPosition(distance, rand() % (HEIGHT - PTERODACTYL_HEIGHT * 2 - TREX_DUCKING_HEIGHT * 2 - 2));
}

void Pterodactyl::Update(float increment)
{
  previousPositionX = sprite->getPosition().x;
  previousPositionY = sprite->getPosition().y;
  sprite->move(-increment, 0);
  if (sprite == pterodactylSprite1 && wingFlapCounter >= LIMB_CHANGE_COUNTER)
  {
    wingFlapCounter = 0;
    sprite = pterodactylSprite2;
    sprite->setPosition(previousPositionX, previousPositionY);
  }
  else if (sprite == pterodactylSprite2 && wingFlapCounter >= LIMB_CHANGE_COUNTER)
  {
    wingFlapCounter = 0;
    sprite = pterodactylSprite1;
    sprite->setPosition(previousPositionX, previousPositionY);
  }
  wingFlapCounter++;
}

Pterodactyl::~Pterodactyl()
{
  delete(pterodactylShape1);
  delete(pterodactylShape2);
  delete(pterodactylSprite1);
  delete(pterodactylSprite2);
}
