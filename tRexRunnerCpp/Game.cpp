#include "Game.h"

TRex* tRex;
Horizon* horizonBump1;
Horizon* horizonBump2;
Pterodactyl* pterodactyl;
std::vector <Cactus*> obstacles;
std::vector <Pterodactyl*> pterodactyls;
sf::Font font;
sf::Text scoreText;
sf::Text gameOverText;
std::stringstream scoreString;
std::stringstream highScoreString;

int numberOfVisibleObstacles;
int obstacleRespawnMaxDistance = WIDTH - OBSTACLE_RESPAWN_BASE_DISTANCE;
int showPterodactyl = SHOW_PTERODACTYL;

int HighScore = 0;
int Score = 0;
int obstacleDistance = 0;
int obstacleRespawnBaseDistance = OBSTACLE_RESPAWN_BASE_DISTANCE;
bool pterodactylPresent = false;
bool firstFrame = false;
bool keyPressed = false;

clock_t beginTime = clock();
clock_t scoreTimer = clock();

float Gravity = GAME_GRAVITY;
float GameSpeed = GAME_INITIAL_SPEED;
float GameSpeedDelta = GAME_SPEED_DELTA;
float JumpingSpeed = JUMPING_SPEED;

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "tRexRunner");

void InitGame()
{
    LoadConfig();
    LoadHighScore();
    font.loadFromFile("Minecraft.ttf");
    scoreText.setFont(font);
    scoreText.setCharacterSize(12);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(0, 0);
    tRex = new TRex();
    horizonBump1 = new Horizon();
    horizonBump2 = new Horizon();
}

void LoadConfig()
{
    // Reading the game config file
    tinyxml2::XMLDocument config;
    tinyxml2::XMLError pError = config.LoadFile("tRexRunnerConfig.xml");
    if (pError == 0)
    {
        const char* sGravity = config.FirstChildElement("GAME_GRAVITY")->GetText();
        Gravity = atof(sGravity);
        const char* sGameSpeed = config.FirstChildElement("GAME_INITIAL_SPEED")->GetText();
        GameSpeed = atof(sGameSpeed);
        const char* sGameSpeedDelta = config.FirstChildElement("GAME_SPEED_DELTA")->GetText();
        GameSpeedDelta = atof(sGameSpeedDelta);
        const char* sJumpingSpeed = config.FirstChildElement("JUMPING_SPEED")->GetText();
        JumpingSpeed = atof(sJumpingSpeed);
    }
    else printf("Config file not found, using defaults.");

}

void LoadHighScore()
{
    // Loading High Score from previous attempts
    std::ifstream FHighScore;
    char c;
    
    if (FHighScore.good())
    {
        FHighScore.open("HighScore.bin", std::ifstream::in);
    while (FHighScore.get(c))
    {
        HighScore *= 10;
        HighScore += (c - 48);
    }
    FHighScore.close();
    }
    else
    {
        std::ofstream FHighScore("HighScore.bin", std::ofstream::out);
        FHighScore << 0;
        FHighScore.close();
    }
}

void WriteScore()
{
    std::ofstream FHighScore("HighScore.bin", std::ofstream::out);
    FHighScore << HighScore;
    FHighScore.close();
}

void Game()
{
    sf::RectangleShape HorizonLine(sf::Vector2f(HORIZON_LENGTH, HORIZON_WIDTH));
    HorizonLine.setPosition(HORIZON_POSITION_X, HORIZON_POSITION_Y);
    while (window.isOpen())
    {
        // Execute only when render period is met
        if (((clock() - beginTime)) > RENDER_PERIOD)
        {
            beginTime = clock();
            srand(beginTime);
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            // Removing obstacles that passed the screen
            if (!obstacles.empty() && obstacles[0]->GetPositionY() < 0)
            {
                obstacles.erase(obstacles.begin());
                numberOfVisibleObstacles--;
            }
            if (!pterodactyls.empty() && pterodactyls[0]->GetPositionY() < 0)
            {
                pterodactyls.erase(pterodactyls.begin());
                numberOfVisibleObstacles--;
            }
            // Adding obstacles to the buffer
            while (numberOfVisibleObstacles < MAX_OBSTACLE_COUNT)
            {
                obstacleDistance += OBSTACLE_RESPAWN_BASE_DISTANCE + rand() % obstacleRespawnMaxDistance;
                if (obstacleDistance >= showPterodactyl)
                {
                    pterodactyls.push_back(new Pterodactyl());
                    pterodactyls[pterodactyls.size() - 1]->Init(obstacleDistance);
                }
                else
                {
                    obstacles.push_back(new Cactus());
                    obstacles[obstacles.size() - 1]->Init(obstacleDistance, rand() % 4 + 1);
                }
                numberOfVisibleObstacles++;
            }
            // Checking if TRex collided with an obstacle
            // and handling the Game over screen
            if (false /*collision*/)
            {
                HorizonLine.setFillColor(sf::Color::Red);
                window.clear();
                window.draw(HorizonLine);
                tRex->Draw(&window);
                window.display();

                if ((GetKeyState(VK_UP) & 0x8000) && !keyPressed)
                {
                    firstFrame = true;
                    HorizonLine.setFillColor(sf::Color::Red);
                    delete tRex;
                    delete horizonBump1;
                    delete horizonBump2;
                    obstacles.clear();
                    if (pterodactyl != NULL)
                        delete pterodactyl;
                    InitGame();
                }
            }
            // If not colliding with anything, continue
            else
            {
                // Handling up and down arrow key presses
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
                // Turning Score into string for display
                std::string temp1 = "", temp2 = "";
                /*scoreString << std::setw(4) << std::setfill('0') << Score;
                temp1 = scoreString.str();
                highScoreString << std::setw(4) << std::setfill('0') << HighScore;
                temp2 = highScoreString.str();*/
                scoreText.setString("HI " + std::to_string(HighScore));
                tRex->Update();
                window.clear();
                window.draw(HorizonLine);
                tRex->Update();
                tRex->Draw(&window);
                window.draw(scoreText);
                // Moving all the obstacles to the left
                // according to current game speed
                // and updating Pterodactyl wing flapping
                for (int i = 0; i < obstacles.size(); i++)
                {
                    obstacles[i]->Move(0.1);
                    obstacles[i]->Draw(&window);
                }
                if (pterodactyl != NULL)
                {
                    pterodactyl->Update();
                    pterodactyl->Move(0.1);
                    pterodactyl->Draw(&window);
                }
                window.display();
            }
        }
        // Score counter handling
        if (clock() - scoreTimer >= GAME_SCORE_INCREMENT)
        {
            scoreTimer = clock();
            Score++;
            if (Score % 100 == 0)
            {
                GameSpeed += GameSpeedDelta;
                obstacleRespawnBaseDistance += OBSTACLE_RESPAWN_DISTANCE_INC;
                obstacleRespawnMaxDistance += OBSTACLE_RESPAWN_DISTANCE_INC;
                showPterodactyl += OBSTACLE_RESPAWN_DISTANCE_INC * 2;
            }
            if (Score > HighScore)
            {
                HighScore = Score;
            }
        }
    }
}

void RunGame()
{
    InitGame();
    Game();
    WriteScore();
}