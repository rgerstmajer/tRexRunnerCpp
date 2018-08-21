#pragma once
#include <SFML\Graphics.hpp>
#include "Globals.h"

class GameObject
{
public:
	GameObject();
	virtual void Draw() = 0;
	virtual void Move() = 0;
	~GameObject();
};

