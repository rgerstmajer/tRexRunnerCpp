//! Pterodactyl.h
/*!
* Pterodactyl subclass
*
* Created: 20.08.2018.
* Author : Robert Gerstmajer
*/
#pragma once
#include "Obstacle.h"
class Pterodactyl :
  public Obstacle
{
public:
  //! constructor
  Pterodactyl(float distance);
  //! Update method
  /*
  * Changes sprite to simulate wing flapping
  */
  void Update(float increment);
  //! Default destructor
  ~Pterodactyl();
private:
  sf::Texture* pterodactylShape1; /*! Texture for loading the pterodactyl1 sprite shape*/
  sf::Sprite* pterodactylSprite1; /*! Sprite for pterodactyl2 shape*/

  sf::Texture* pterodactylShape2; /*! Texture for loading the pterodactyl1 sprite shape*/
  sf::Sprite* pterodactylSprite2; /*! Sprite for pterodactyl2 shape*/

  int wingFlapCounter; /*! Counter for swaping shapes to 'flap wings'*/
  float randomHight; /*! Random height for pterodactyl to make it avoidable by tRex*/
  float previousPositionX; /*! Previous position X when swapping sprites*/
  float previousPositionY; /*! Previous position Y when swapping sprites*/
};

