#pragma once
#include "Game.h"
#include <vld.h>
void main()
{
  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), GAME_NAME);
  Game game(&window);
  game.RunGame();
}