#pragma once
#include "GameObject.h"
class Horizon :
    public GameObject
{

public:
    Horizon();
    gameObjectType GetGameObjectType() { return HORIZON; }
    void Move();
    void Draw();
    ~Horizon();
};

