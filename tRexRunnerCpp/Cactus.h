//! Cactus.h
/*!
 * Cactus subclass
 * 
 * Created: 20.08.2018.
 * Author : Robert Gerstmajer
 */
#pragma once
#include "Obstacle.h"
class Cactus :
  public Obstacle
{
  public:
  //! Default constructot
  Cactus(float distance, int type);
  //! Update method
  /*!
  * Moves sprite to the left according to increment
  * \param increment How much to move the sprite
  */
  void Update(float increment);
  //! Default destructor
  virtual ~Cactus();
  private:
  sf::Texture* cactusShape; /*! Texture for loading the cactus sprite shape*/
};

