#pragma once
#include "Obstacle.h"
class Cactus :
	public Obstacle
{
public:
	Cactus();
	void Draw();
	void Move();
	~Cactus();
};

