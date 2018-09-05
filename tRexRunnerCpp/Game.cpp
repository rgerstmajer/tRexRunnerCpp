#include "Game.h"

TRex *tRex;
Cactus *cactus;
Pterodactyl *pterodactyl;
Horizon *horizon;

bool firstFrame = false;
bool keyPressed = false;

clock_t beginTime = clock();
std::vector<Obstacle> obstacles;

int GRAVITY, GAME_SPEED, GAME_SPEED_DELTA, JUMPING_SPEED;
sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "tRexRunner");

void InitGame()
{
    tRex = new TRex();
    cactus = new Cactus();
    pterodactyl = new Pterodactyl();
    horizon = new Horizon();

    cactus->Init();
    pterodactyl->Init();
}

void Run()
{
    sf::RectangleShape line(sf::Vector2f(HORIZON_LENGTH, HORIZON_WIDTH));
    line.setPosition(HORIZON_POSITION_X, HORIZON_POSITION_Y);
    while (window.isOpen())
    {
        if (((clock() - beginTime)) < RENDER_PERIOD)
        {

        }
        else
        {
            beginTime = clock();

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            //colliding
            if (tRex->Colliding(cactus) || tRex->Colliding(pterodactyl))
            {
                line.setFillColor(sf::Color::Red);
                window.clear();
                window.draw(line);
                cactus->Draw(&window);
                pterodactyl->Draw(&window);
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
                if (tRex->State == TRex::RUNNING1 || tRex->State == TRex::RUNNING2)
                {
                    if (GetKeyState(VK_UP) & 0x8000)
                    {
                        keyPressed = true;
                        tRex->Jump();
                    }
                    else if (GetKeyState(VK_DOWN) & 0x8000)
                    {
                        keyPressed = true;
                        tRex->Duck();
                    }
                    else
                    {
                        tRex->Run();
                    }
                    tRex->Update();
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
                pterodactyl->Draw(&window);
                if (firstFrame)
                {
                    firstFrame = false;
                }
                else
                {
                    cactus->Move(1.0);
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

void RunGame()
{
    InitGame();
    Run();
}
