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
  } m_state;
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
  float m_Gravity;      /*! Determines speed of falling*/
  float m_JumpingSpeed; /*! Determines speed of rising*/

  int  m_stepCounter = 1;     /*! Used for determening when to change sprites for stepping animation*/
  bool m_dropping    = false; /*! Used for detemening if tRex reached its maximum height*/

  sf::Texture *m_standingShape  = NULL;  /*! Texture for loading the tRex standing sprite shape*/
  sf::Sprite  *m_standingSprite = NULL;  /*! Sprite for tRex standing shape*/
               
  sf::Texture *m_runningShape1  = NULL;  /*! Texture for loading the tRex running1 sprite shape*/
  sf::Sprite  *m_runningSprite1 = NULL;  /*! Sprite for tRex running1 shape*/
               
  sf::Texture *m_runningShape2  = NULL;  /*! Texture for loading the tRex running2 sprite shape*/
  sf::Sprite  *m_runningSprite2 = NULL;  /*! Sprite for tRex running2 shape*/

  sf::Texture *m_duckingShape1  = NULL;  /*! Texture for loading the tRex ducking1 sprite shape*/
  sf::Sprite  *m_duckingSprite1 = NULL;  /*! Sprite for tRex ducking1 shape*/

  sf::Texture *m_duckingShape2  = NULL;  /*! Texture for loading the tRex ducking2 sprite shape*/
  sf::Sprite  *m_duckingSprite2 = NULL;  /*! Sprite for tRex ducking2 shape*/

  sf::Texture *m_deadShape      = NULL;  /*! Texture for loading the tRex crashed sprite shape*/
  sf::Sprite  *m_deadSprite     = NULL;  /*! Sprite for tRex crashed shape*/
};
