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
  sf::Texture* m_pterodactylShape1 = NULL; /*! Texture for loading the pterodactyl1 sprite shape*/
  sf::Sprite* m_pterodactylSprite1 = NULL; /*! Sprite for pterodactyl2 shape*/

  sf::Texture* m_pterodactylShape2 = NULL; /*! Texture for loading the pterodactyl1 sprite shape*/
  sf::Sprite* m_pterodactylSprite2 = NULL; /*! Sprite for pterodactyl2 shape*/

  int   m_wingFlapCounter;   /*! Counter for swapping shapes to 'flap wings'*/
  float m_randomHight;       /*! Random height for pterodactyl to make it avoidable by tRex*/
  float m_previousPositionX; /*! Previous position X when swapping sprites*/
  float m_previousPositionY; /*! Previous position Y when swapping sprites*/
};

