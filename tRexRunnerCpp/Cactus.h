#pragma once
#include "Obstacle.h"
class Cactus :
    public Obstacle
{
  public:
    Cactus();
    gameObjectType GetGameObjectType() { return CACTUS; }
    void Init(int distance, int type);
    void Init();
    ~Cactus();
  private:
    sf::Texture* CactusShape1;
    sf::Texture* CactusShape2;
    sf::Texture* CactusShape3;
    sf::Texture* CactusShape4;
};

