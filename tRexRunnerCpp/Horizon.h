//! Horizon.h
/*!
* Horizon subclass for horizon bumps
*
* Created: 20.08.2018.
* Author : Robert Gerstmajer
*/
#pragma once
#include "GameObject.h"
class Horizon :
    public GameObject
{
    sf::RectangleShape* line;
public:
    //! Constructor
    /*!
    * Horizon bump constructr
    * \param type Type of bump (1 or 2)
    */
    Horizon(int type);
    //! Move method
    /*!
    * Moves sprite to the left according to increment
    * \param increment How much to move the sprite
    */
    void Move(float increment);
    //! Default destructor
    ~Horizon();
private:
    sf::Texture* bump;/*! Texture for loading the bump1 and bump2 sprite shapes*/
};

