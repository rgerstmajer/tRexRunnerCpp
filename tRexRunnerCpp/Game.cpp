#include "Game.h"

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "tRexRunner");

void InitGame()
{
    LoadConfig();
    LoadHighScore();
    LoadTextFields();
    Score = 0;
    tRex = new TRex(JumpingSpeed, Gravity);
    horizonBump1 = new Horizon(1);
    horizonBump2 = new Horizon(2);
}

void LoadTextFields()
{
    font.loadFromFile("Minecraft.ttf");
    scoreText.setFont(font);
    scoreText.setCharacterSize(12);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(WIDTH / 2, 0);
    highScoreText.setFont(font);
    highScoreText.setCharacterSize(12);
    highScoreText.setFillColor(sf::Color::White);
    highScoreText.setPosition(0, 0);
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(15);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setString("GAME OVER");
    gameOverText.setPosition(WIDTH/3, HEIGHT/3);
}

void LoadConfig()
{
    // Reading the game config file
    tinyxml2::XMLDocument config;
    system("dir");
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
    HighScore = 0;
    
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
    sf::RectangleShape HorizonLineGap(sf::Vector2f(TREX_STANDING_WIDTH, HORIZON_WIDTH * 2));
    HorizonLineGap.setPosition(TREX_STARTING_POSITION_X + TREX_STANDING_WIDTH / 3, HORIZON_POSITION_Y - 1);
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
            // Handling TRex padding
            if (tRex->GetPositionY() == TREX_STARTING_POSITION_Y)
            {
                HorizonLineGap.setFillColor(sf::Color::Black);
            }
            else
            {
                HorizonLineGap.setFillColor(sf::Color::Transparent);
            }
            // Removing obstacles that passed the screen
            if (!obstacles.empty() && obstacles[0]->GetPositionX() < 0)
            {
                obstacles.erase(obstacles.begin());
                numberOfVisibleObstacles--;
            }
            if (!pterodactyls.empty() && pterodactyls[0]->GetPositionX() < 0)
            {
                pterodactyls.erase(pterodactyls.begin());
                numberOfVisibleObstacles--;
            }
            //If there were already obstacles, they will move according
            //the game speed. If there are new ones, they will be 
            //handled in the obstacle creation loop
            if (numberOfVisibleObstacles == 0)
            {
                lastDistance = 0;
            }
            if (lastDistance != 0)
            {
                lastDistance -= GameSpeed;
            }
            // Adding obstacles to the buffer
            while (numberOfVisibleObstacles < MAX_OBSTACLE_COUNT)
            {
                obstacleDistance = OBSTACLE_RESPAWN_BASE_DISTANCE + rand() % obstacleRespawnMaxDistance;
                if (obstacleDistance >= showPterodactyl)
                {
                    pterodactyls.push_back(new Pterodactyl());
                    pterodactyls[pterodactyls.size() - 1]->Init(obstacleDistance + lastDistance);
                    lastDistance = pterodactyls[pterodactyls.size() - 1]->GetPositionX();
                }
                else
                {
                    obstacles.push_back(new Cactus());
                    obstacles[obstacles.size() - 1]->Init(obstacleDistance + lastDistance, rand() % 4 + 1);
                    lastDistance = obstacles[obstacles.size() - 1]->GetPositionX();
                }
                numberOfVisibleObstacles++;
            }
            // Checking if TRex collided with an obstacle
            // and handling the Game over screen
            if ((!obstacles.empty() && tRex->Colliding(obstacles[0])) || (!pterodactyls.empty() && tRex->Colliding(pterodactyls[0])))
            {
                HorizonLine.setFillColor(sf::Color::Red);
                window.clear();
                window.draw(HorizonLine);
                WriteScore();
                tRex->Crash();
                tRex->Draw(&window);
                window.draw(highScoreText);
                window.draw(scoreText);
                window.draw(gameOverText);
                window.display();
                if (!(GetKeyState(VK_UP) & 0x8000) && !(GetKeyState(VK_DOWN) & 0x8000))
                {
                    keyPressed = false;
                }
                if ((GetKeyState(VK_UP) & 0x8000) && !keyPressed) // To not restart game while holding down the UP arrow key
                {
                    firstFrame = true;
                    HorizonLine.setFillColor(sf::Color::White);
                    delete horizonBump1;
                    delete horizonBump2;
                    if (!obstacles.empty())
                    {
                        obstacles.clear();
                    }
                    if (!pterodactyls.empty())
                    {
                        pterodactyls.clear();
                    }
                    numberOfVisibleObstacles = 0;
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
                        showPterodactyl += OBSTACLE_RESPAWN_DISTANCE_INC;
                    }
                    if (Score > HighScore)
                    {
                        HighScore = Score;
                    }
                }
                // Clearing window buffer
                window.clear();
                // Drawing the HighScore and Score text fields
                highScoreText.setString("HI " + std::to_string(HighScore));
                scoreText.setString(std::to_string(Score));
                window.draw(highScoreText);
                window.draw(scoreText);
                // Updating TRex steps
                tRex->Update();
                // Drawing Horizon and bumps
                window.draw(HorizonLine);
                horizonBump1->Draw(&window);
                horizonBump2->Draw(&window);
                window.draw(HorizonLineGap);
                // Drawing TRex
                tRex->Draw(&window);
                // Moving all the obstacles and bumps 
                // to the left according to current game speed
                // and updating Pterodactyl wing flapping
                horizonBump1->Move(GameSpeed);
                horizonBump2->Move(GameSpeed);
                for (int i = 0; i < obstacles.size(); i++)
                {
                    obstacles[i]->Move(GameSpeed);
                    obstacles[i]->Draw(&window);
                }
                for (int i = 0; i < pterodactyls.size(); i++)
                {
                    pterodactyls[i]->Update();
                    pterodactyls[i]->Move(GameSpeed);
                    pterodactyls[i]->Draw(&window);
                }
                // Displaying whats drawn
                window.display();
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