#pragma once
#include "Obstacle.h"
class Cactus :
    public Obstacle
{
private:
    sf::Texture* CactusShape1;
    sf::Sprite*  CactusSprite1;

    sf::Texture* CactusShape2;
    sf::Sprite*  CactusSprite2;

    sf::Texture* CactusShape3;
    sf::Sprite*  CactusSprite3;

    sf::Texture* CactusShape4;
    sf::Sprite*  CactusSprite4;
public:

    

    Cactus();
    void Draw(sf::RenderWindow* window);
    void Init();
    ~Cactus();
};

