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
  } state;
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
  //! Update method
  /*!
  * If the tRex is running or ducking, change sprites
  * to look like it's taking steps
  */
  void Update();
  //! Default destructor
  ~TRex();
private:
  int stepCounter = 1; /*! Used for determening when to change sprites for stepping animation*/
  float m_Gravity; /*! Determines speed of falling*/
  float m_JumpingSpeed; /*! Determines speed of rising*/
  bool dropping = false; /*! Used for detemening if tRex reached its maximum height*/

  sf::Texture *standingShape;  /*! Texture for loading the tRex standing sprite shape*/
  sf::Sprite  *standingSprite; /*! Sprite for tRex standing shape*/

  sf::Texture *runningShape1;  /*! Texture for loading the tRex running1 sprite shape*/
  sf::Sprite  *runningSprite1; /*! Sprite for tRex running1 shape*/

  sf::Texture *runningShape2;  /*! Texture for loading the tRex running2 sprite shape*/
  sf::Sprite  *runningSprite2; /*! Sprite for tRex running2 shape*/

  sf::Texture *duckingShape1;  /*! Texture for loading the tRex ducking1 sprite shape*/
  sf::Sprite  *duckingSprite1; /*! Sprite for tRex ducking1 shape*/

  sf::Texture *duckingShape2;  /*! Texture for loading the tRex ducking2 sprite shape*/
  sf::Sprite  *duckingSprite2; /*! Sprite for tRex ducking2 shape*/

  sf::Texture *deadShape;    /*! Texture for loading the tRex crashed sprite shape*/
  sf::Sprite  *deadSprite;   /*! Sprite for tRex crashed shape*/
};
