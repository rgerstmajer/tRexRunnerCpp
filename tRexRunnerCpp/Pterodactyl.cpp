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
  PterodactylShape1 = new sf::Texture();
  PterodactylShape2 = new sf::Texture();

  PterodactylSprite1 = LoadShape(PterodactylShape1, PTERODACTYL_HEIGHT, PTERODACTYL_WIDTH, pterodactyl1);
  PterodactylSprite2 = LoadShape(PterodactylShape2, PTERODACTYL_HEIGHT, PTERODACTYL_WIDTH, pterodactyl2);

  sprite = PterodactylSprite1;
  sprite->setPosition(distance, rand() % (HEIGHT - PTERODACTYL_HEIGHT * 2 - TREX_DUCKING_HEIGHT * 2 - 2));
}

void Pterodactyl::Update(float increment)
{
  previousPositionX = sprite->getPosition().x;
  previousPositionY = sprite->getPosition().y;
  sprite->move(-increment, 0);
  if (sprite == PterodactylSprite1 && wingFlapCounter >= LIMB_CHANGE_COUNTER)
  {
    wingFlapCounter = 0;
    sprite = PterodactylSprite2;
    sprite->setPosition(previousPositionX, previousPositionY);
  }
  else if (sprite == PterodactylSprite2 && wingFlapCounter >= LIMB_CHANGE_COUNTER)
  {
    wingFlapCounter = 0;
    sprite = PterodactylSprite1;
    sprite->setPosition(previousPositionX, previousPositionY);
  }
  wingFlapCounter++;
}

Pterodactyl::~Pterodactyl()
{
  delete PterodactylShape1;
  delete PterodactylShape2;
  delete PterodactylSprite1;
  delete PterodactylSprite2;
  PterodactylShape1  = NULL;
  PterodactylShape2  = NULL;
  PterodactylSprite1 = NULL;
  PterodactylSprite2 = NULL;
}
