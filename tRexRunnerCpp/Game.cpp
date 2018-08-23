#include "Game.h"

TRex *tRex;
Cactus *cactus;
Pterodactyl *pterodactyl;
Horizon *horizon;

clock_t beginTime = clock();

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "tRexRunner");

void InitGame()
{
	tRex = new TRex();
	cactus = new Cactus();
	pterodactyl = new Pterodactyl();
	horizon = new Horizon();
}

void Run()
{
    sf::RectangleShape line(sf::Vector2f(256, 2));
    cactus->Init();
    line.setPosition(0, 50);
    while (window.isOpen())
    {
        if (((clock() - beginTime)) < 17)
        {
            
        }
        else
        {
            beginTime = clock();
            tRex->Run();
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            line.setFillColor(sf::Color::White);
            //TODO Check collision
            if (Colliding())
            {
                line.setFillColor(sf::Color::Red);
                window.clear();
                window.draw(line);
                cactus->Draw(&window);
                tRex->Draw(&window);
                window.display();

                if (GetKeyState(VK_UP) & 0x8000)
                {
                    line.setFillColor(sf::Color::Red);
                    InitGame();
                }
            }
            else
            {
                if (tRex->State == TRex::RUNNING)
                {
                    if (GetKeyState(VK_UP) & 0x8000)
                    {
                        tRex->Jump();
                    }
                    else if (GetKeyState(VK_DOWN) & 0x8000)
                    {
                        tRex->Duck();
                    }
                }
                else
                {
                    if (tRex->State == TRex::JUMPING)
                        tRex->Jump();
                    else
                        switch (tRex->State)
                        {
                        case TRex::JUMPING:
                            tRex->Jump();
                            break;
                        case TRex::DUCKING:
                            tRex->Duck();
                            break;
                        case TRex::RUNNING:
                            tRex->Run();
                            break;
                        }
                    line.setFillColor(sf::Color::White);
                }
                cactus->Move();
                window.clear();
                window.draw(line);
                cactus->Draw(&window);
                tRex->Draw(&window);
                window.display();
            }
        }
    }
}


bool Colliding()
{
    bool isCollision = false;

    /*int tRexCenterX = tRex->getPositionX() + tRex->getRadius();
    int tRexCenterY = tRex->getPositionY() + tRex->getRadius();

    int cactusCenterX = cactus->getPositionX() + cactus->getRadius();
    int cactusCenterY = cactus->getPositionY() + cactus->getRadius();

    if (tRexCenterX < cactusCenterX)
    {
        isCollision = (sqrt((cactusCenterX - tRexCenterX) ^ 2 + (cactusCenterY - tRexCenterY) ^ 2) > (cactus->getRadius() + tRex->getRadius())) ? isCollision = false : isCollision = true;
    }*/

    return isCollision;
}

void RunGame()
{
	InitGame();
	Run();
}