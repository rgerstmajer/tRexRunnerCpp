#include "Horizon.h"



Horizon::Horizon()
{
    line = new sf::RectangleShape(sf::Vector2f(HORIZON_LENGTH, HORIZON_WIDTH));
}

void Horizon::Move() //Move details from right to left
{

}

void Horizon::Draw(sf::RenderWindow* window)
{
    window->draw(*line);
}

void Horizon::Init()
{

}

Horizon::~Horizon()
{
}
