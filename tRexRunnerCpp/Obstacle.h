#pragma once
#include "GameObject.h"
class Obstacle :
    public GameObject
{
public:
    Obstacle();
    gameObjectType GetGameObjectType() { return OBSTACLE; }
    void Move(float increment);
    ~Obstacle();
};

