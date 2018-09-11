//! GameObject.h
/*!
* GameObject base class header file
*
* Created: 20.08.2018.
* Author : Robert Gerstmajer
*/
#pragma once
#include <SFML\Graphics.hpp>
#include "Globals.h"

class GameObject
{
  public:
    //! Default constructor
    GameObject();
    //! Drawing method
    /*!
    * Draws sprite on sfml RenderWindow
    * \param window sfml RenderWindow to draw on
    */
    void Draw(sf::RenderWindow* window);
    //! Collision checking method
    /*!
    * Checks if the GameObject sprite is colliding
    * with obstacle
    * \param obstacle to check collision with
    */
    bool Colliding(GameObject* obstacle);
    /*! Returns the sprite location on X axis
    */
    float GetPositionX() { return sprite->getPosition().x; }
    /*! Returns the sprite location on Y axis
    */
    float GetPositionY() { return sprite->getPosition().y; }
    virtual void Init() = 0;
    //! Default destructor
    ~GameObject();
protected:
    enum gameObjectType
    {
        TREX,
        PTERODACTYL,
        CACTUS,
        HORIZON
    };

    sf::Sprite* sprite; /* The current object's sprite */
    //! Shape loading method
    /*!
    * Loads shape into sprite
    * \param texture sfml Texture buffer for creating the sprite
    * \param height sprite height
    * \param width sprite width
    * \param shape spriteShape taken from Globals.h
    * \param isBump if the shape is a horizon bump, background
    * is black, otherwise transparent
    */
    sf::Sprite* LoadShape(sf::Texture* texture, const int height, const int width, const unsigned char* shape, bool isBump = false);
};
