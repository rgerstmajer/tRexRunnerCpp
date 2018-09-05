#pragma once
#include "GameObject.h"

class TRex :
    public GameObject
{
private:
    int stepCounter = 0;

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
public:
    enum TRexStates
    {
        STANDING,

        RUNNING,
        RUNNING1,
        RUNNING2,

        JUMPING,

        DUCKING,
        DUCKING1,
        DUCKING2,

        CRASHED
    } State;

    TRex();
    void Jump();
    void Duck();
    void Run();
    void Init();

    gameObjectType GetGameObjectType() { return TREX; }
    void Update();

    ~TRex();
};
