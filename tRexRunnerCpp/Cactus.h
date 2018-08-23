#pragma once
#include "Obstacle.h"
class Cactus :
	public Obstacle
{
public:
	Cactus();
	void Draw(sf::RenderWindow* window);
    void Init();
	void Move();
	~Cactus();
};

