#pragma once
#include "GameObject.h"

class TRex :
    public GameObject
{
private:
    int stepCounter = 0;
    float m_Gravity;
    float m_JumpingSpeed;

    sf::Texture *StandingShape;
    sf::Sprite  *StandingSprite;

    sf::Texture *RunningShape1;
    sf::Sprite  *RunningSprite1;

    sf::Texture *RunningShape2;
    sf::Sprite  *RunningSprite2;

    sf::Texture *DuckingShape1;
    sf::Sprite  *DuckingSprite1;

    sf::Texture *DuckingShape2;
    sf::Sprite  *DuckingSprite2;

    sf::Texture *DeadShape;
    sf::Sprite  *DeadSprite;
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

    TRex(float jumpingSpeed, float gravity);
    void Jump();
    void Duck();
    void Run();
    void Crash();
    void Init();

    gameObjectType GetGameObjectType() { return TREX; }
    void Update();

    ~TRex();
};
