#include "Game.h"

TRex *tRex;
Cactus *cactus;
Pterodactyl *pterodactyl;
Horizon *horizon;

bool firstFrame = false;

clock_t beginTime = clock();


sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "tRexRunner");

void InitGame()
{
    tRex = new TRex();
    cactus = new Cactus();
    pterodactyl = new Pterodactyl();
    horizon = new Horizon();

    LoadShapes();
    cactus->Init();
}

void Run()
{
    sf::RectangleShape line(sf::Vector2f(256, 1));
    line.setPosition(0, 50);
    while (window.isOpen())
    {
        if (((clock() - beginTime)) < 20)
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
            if (/*Colliding()*/false)
            {
                line.setFillColor(sf::Color::Red);
                window.clear();
                window.draw(line);
                cactus->Draw(&window);
                tRex->Draw(&window);
                window.display();

                if (GetKeyState(VK_UP) & 0x8000)
                {
                    firstFrame = true;
                    line.setFillColor(sf::Color::Red);
                    
                    delete tRex;
                    delete cactus;
                    delete horizon;
                    InitGame();

                }
            }
            else
            {
                if (tRex->State == TRex::STANDING)
                {
                    tRex->State = TRex::RUNNING1;
                }
                if (tRex->State == TRex::RUNNING1 || tRex->State == TRex::RUNNING2)
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
                        case TRex::DUCKING1:
                            tRex->Duck();
                            break;
                        case TRex::DUCKING2:
                            tRex->Duck();
                            break;
                        case TRex::RUNNING1:
                            tRex->Run();
                            break;
                        case TRex::RUNNING2:
                            tRex->Run();
                            break;
                        }
                    line.setFillColor(sf::Color::White);
                }
                window.clear();
                window.draw(line);
                tRex->Draw(&window);
                window.draw(*tRex->StandingSprite);
                if (firstFrame)
                    firstFrame = false;
                else
                {
                    cactus->Move();
                    cactus->Draw(&window);
                }
                
                window.display();
            }
        }
    }
}


//bool Colliding()
//{
//    bool isCollision = false;
//
//    int tRexCenterX = tRex->getPositionX() + tRex->getRadius();
//    int tRexCenterY = tRex->getPositionY() + tRex->getRadius();
//
//    int cactusCenterX = cactus->getPositionX() + cactus->getRadius();
//    int cactusCenterY = cactus->getPositionY() + cactus->getRadius();
//
//    int xDistance = cactusCenterX - tRexCenterX;
//    int yDistance = cactusCenterY - tRexCenterY;
//    float distance = sqrt(pow(xDistance, 2) + pow(yDistance, 2));
//    int maxAllowedDistance = cactus->getRadius() + tRex->getRadius();
//
//    if (tRexCenterX < cactusCenterX)
//    {
//        if (distance > maxAllowedDistance)
//            isCollision = false;
//        else
//            isCollision = true;
//    }
//
//    return isCollision;
//}

void LoadShapes()
{

}

void RunGame()
{
    InitGame();
    Run();
}
