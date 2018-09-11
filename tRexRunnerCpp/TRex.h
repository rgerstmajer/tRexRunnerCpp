//! TRex.h
/*!
* TRex subclass
*
* Created: 20.08.2018.
* Author : Robert Gerstmajer
*/
#pragma once
#include "GameObject.h"

class TRex :
    public GameObject
{
public:
    enum TRexStates
    {
        STANDING,
        RUNNING1,
        RUNNING2,

        JUMPING,

        DUCKING1,
        DUCKING2,

        CRASHED
    } State;
    //! TRex constuctor
    /*!
    * \param jumpingSpeed loaded from config, how many pixels will the tRex rise each frame
    * \param gravity loaded from config, how many pixels will the tRex drop each frame
    */
    TRex(float jumpingSpeed, float gravity);
    //! Jump method
    /*!
    * Moves the tRex up and drops it after reaching max height
    */
    void Jump();
    //! Duck method
    /*!
    * Changes tRex sprite to ducking, lowering its height
    */
    void Duck();
    //! Run method
    /*!
    * If the tRex is jumping, do nothing;
    * If the tRex is on the ground or ducking, make it run normally
    */
    void Run();
    //! Crash method
    /*
    * Changes tRex sprite to display crash
    */
    void Crash();
    void Init();

    gameObjectType GetGameObjectType() { return TREX; }
    //! Update method
    /*!
    * If the tRex is running or ducking, change sprites
    * to look like it's taking steps
    */
    void Update();
    //! Default destructor
    ~TRex();
private:
    int stepCounter = 0; /*! Used for determening when to change sprites for stepping*/
    float m_Gravity; /*! Determens speed of falling*/
    float m_JumpingSpeed; /*! Determens speed of rising*/

    sf::Texture *StandingShape;  /*! Texture for loading the tRex standing sprite shape*/
    sf::Sprite  *StandingSprite; /*! Sprite for tRex standing shape*/

    sf::Texture *RunningShape1;  /*! Texture for loading the tRex running1 sprite shape*/
    sf::Sprite  *RunningSprite1; /*! Sprite for tRex running1 shape*/

    sf::Texture *RunningShape2;  /*! Texture for loading the tRex running2 sprite shape*/
    sf::Sprite  *RunningSprite2; /*! Sprite for tRex running2 shape*/

    sf::Texture *DuckingShape1;  /*! Texture for loading the tRex ducking1 sprite shape*/
    sf::Sprite  *DuckingSprite1; /*! Sprite for tRex ducking1 shape*/

    sf::Texture *DuckingShape2;  /*! Texture for loading the tRex ducking2 sprite shape*/
    sf::Sprite  *DuckingSprite2; /*! Sprite for tRex ducking2 shape*/

    sf::Texture *DeadShape;      /*! Texture for loading the tRex crashed sprite shape*/
    sf::Sprite  *DeadSprite;     /*! Sprite for tRex crashed shape*/
};
