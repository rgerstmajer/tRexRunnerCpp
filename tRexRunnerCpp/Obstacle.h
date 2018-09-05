#pragma once
#include "GameObject.h"
class Obstacle :
    public GameObject
{
public:
    Obstacle();
    void Move(float increment);
    ~Obstacle();
};

