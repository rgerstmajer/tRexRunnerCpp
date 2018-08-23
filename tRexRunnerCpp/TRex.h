#pragma once
#include "GameObject.h"
class TRex :
	public GameObject
{
public:
    enum TRexStates
    {
        RUNNING,
        JUMPING,
        DUCKING
    } State;

	TRex();
	void Draw(sf::RenderWindow* window);
    void Jump();
    void Duck();
    void Run();

    


	gameObjectType GetGameObjectType() { return TREX; }
    void Move();
	void Move(TRex::TRexStates newState);

	

	~TRex();
};

