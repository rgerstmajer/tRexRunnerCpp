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
    ~Cactus();
  private:
    sf::Texture* CactusShape1; /*! Texture for loading the cactus1 sprite shape*/
    sf::Texture* CactusShape2; /*! Texture for loading the cactus2 sprite shape*/
    sf::Texture* CactusShape3; /*! Texture for loading the cactus3 sprite shape*/
    sf::Texture* CactusShape4; /*! Texture for loading the cactus4 sprite shape*/
};

