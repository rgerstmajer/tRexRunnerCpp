#include "GameObject.h"



GameObject::GameObject()
{
    sprite = new sf::CircleShape(10);
    sprite->setFillColor(sf::Color::Transparent);
}

void GameObject::Draw(sf::RenderWindow* window) // Display the sprite
{

}

GameObject::~GameObject()
{

}
