#pragma once
#include "GameObject.h"
class TRex :
    public GameObject
{
private:
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
        DUCKING2
    } State;

    TRex();
    //void Draw(sf::RenderWindow* window);
    void Jump();
    void Duck();
    void Run();
    void Init();

    gameObjectType GetGameObjectType() { return TREX; }
    void Move();
    void Move(TRex::TRexStates newState);

    sf::Uint8 StandingOrRunningPixels[TREX_DUCKING_HEIGHT * TREX_DUCKING_WIDTH * 4];

    sf::Texture* StandingShape;
    sf::Sprite*  StandingSprite;

    sf::Texture *RunningShape1;
    sf::Sprite  *RunningSprite1;

    sf::Texture *RunningShape2;
    sf::Sprite  *RunningSprite2;

    sf::Uint8 DuckingPixels[TREX_DUCKING_HEIGHT * TREX_DUCKING_WIDTH * 4];

    sf::Texture *DuckingShape1;
    sf::Sprite  *DuckingSprite1;
                
    sf::Texture *DuckingShape2;
    sf::Sprite  *DuckingSprite2;

    void LoadShapes();

    ~TRex();
};
