#pragma once
#include "Obstacle.h"
class Cactus :
    public Obstacle
{
  public:
    Cactus();
    gameObjectType GetGameObjectType() { return CACTUS; }
    void Draw(sf::RenderWindow* window);
    void Init(int distance);
    ~Cactus();
  private:
    sf::Texture* CactusShape1;
    sf::Texture* CactusShape2;
    sf::Texture* CactusShape3;
    sf::Texture* CactusShape4;
};

