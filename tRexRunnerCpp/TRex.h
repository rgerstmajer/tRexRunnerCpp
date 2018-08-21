#pragma once
#include "GameObject.h"
class TRex :
	public GameObject
{
public:
	TRex();
	void Draw();
	gameObjectType GetGameObjectType() { return TREX; }
	void Move();

	enum TRexStates
	{
		RUNNING,
		JUMPING,
		DUCKING
	};

	~TRex();
};

