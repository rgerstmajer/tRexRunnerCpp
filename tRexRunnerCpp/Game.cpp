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

void Game()
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
                    keyPressed = false;
                    tRex->Run();
                }
                tRex->Update();
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

void RunGame()
{
    InitGame();
    Game();
}