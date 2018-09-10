#pragma once
#include "GameObject.h"
class Horizon :
    public GameObject
{
    sf::RectangleShape* line;
public:
    Horizon(int type);
    gameObjectType GetGameObjectType() { return HORIZON; }
    void Move(float increment);
    void Init();
    ~Horizon();
private:
    sf::Texture* bump;
};

