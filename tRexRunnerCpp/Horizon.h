#pragma once
#include "GameObject.h"
class Horizon :
    public GameObject
{
    sf::RectangleShape* line;
public:
    Horizon();
    gameObjectType GetGameObjectType() { return HORIZON; }
    void Move();
    void Draw(sf::RenderWindow* window);
    void Init();
    ~Horizon();
};

