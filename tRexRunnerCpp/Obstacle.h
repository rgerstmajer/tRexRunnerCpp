//! Obstacle.h
/*!
* Obstacle subclass for pterodactyls and cacti
*
* Created: 20.08.2018.
* Author : Robert Gerstmajer
*/
#pragma once
#include "GameObject.h"
class Obstacle :
    public GameObject
{
public:
    //! Default constructor
    Obstacle();
    //! Move method
    /*!
    * Moves sprite to the left according to increment
    * \param increment How much to move the sprite
    */
    void Move(float increment);

    //! Default destructor
    ~Obstacle();
};
