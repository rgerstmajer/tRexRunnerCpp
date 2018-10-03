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
  //! Initialization method
  /*!
   * Initializes random cactus sprite
   * on random distance.
   * 
   * \param distance Distance of the cactus being initialized
   * \param type Type of cactus (1-4)
   */
  void Init(int distance, int type);
  //! Update method
  /*!
  * Moves sprite to the left according to increment
  * \param increment How much to move the sprite
  */
  void Update(float increment);
  //! Default destructor
  virtual ~Cactus();
  private:
  sf::Texture* CactusShape; /*! Texture for loading the cactus sprite shape*/
};

