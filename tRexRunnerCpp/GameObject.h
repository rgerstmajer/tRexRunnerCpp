#pragma once
#include <SFML\Graphics.hpp>
#include "Globals.h"

class GameObject
{
protected:
    sf::CircleShape* sprite;
public:
	GameObject();
    virtual void Draw(sf::RenderWindow* window);

    float getPositionX() { return sprite->getPosition().x; }
    float getPositionY() { return sprite->getPosition().y; }
    float getRadius() { return sprite->getRadius(); }

	~GameObject();
};

