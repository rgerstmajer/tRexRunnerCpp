#pragma once
#include "GameObject.h"
class Obstacle :
	public GameObject
{
public:
	Obstacle();
	gameObjectType GetGameObjectType() { return OBSTACLE; }
	~Obstacle();
};

