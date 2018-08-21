#pragma once
#include <SFML\Graphics.hpp>
#include "Globals.h"

class GameObject
{
private:
	
public:
	GameObject();
	virtual void Draw() = 0;
	virtual void Move() = 0;
	virtual gameObjectType GetGameObjectType() = 0;
	~GameObject();
};

