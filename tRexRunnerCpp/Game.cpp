#include "Game.h"

TRex *tRex;
Cactus *cactus;
Pterodactyl *pterodactyl;
Horizon *horizon;
sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "tRexRunner");

void InitGame()
{
	tRex = new TRex();
	cactus = new Cactus();
	pterodactyl = new Pterodactyl();
	horizon = new Horizon();
}

void Draw()
{
	horizon->Draw();
	tRex->Draw();
	cactus->Draw();
	pterodactyl->Draw();
	window.clear();
	window.display();
}

void RunGame()
{
	InitGame();
	Draw();
}