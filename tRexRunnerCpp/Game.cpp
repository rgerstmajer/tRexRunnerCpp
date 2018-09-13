#include "Game.h"

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "tRexRunner");

void InitGame()
{
    horizonLineGap.setPosition(TREX_STARTING_POSITION_X + TREX_STANDING_WIDTH / 3, HORIZON_POSITION_Y - 1);
    horizonLine.setPosition(HORIZON_POSITION_X, HORIZON_POSITION_Y);
    score = 0;
    highScore = 0;
    firstFrame = false;
    numberOfVisibleObstacles = 0;
    LoadConfig();
    LoadHighScore();
    LoadTextFields();
    tRex = new TRex(jumpingSpeed, gravity);
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
    tinyxml2::XMLError pError = config.LoadFile("tRexRunnerConfig.xml");
    if (pError != 0)
    {
        printf("Config file not found, using defaults:\nGravity: %f\nGameSpeed: %f\nGameSpeedDelta: %f\nJumpingSpeed: %f", gravity, gameSpeed, gameSpeedDelta, jumpingSpeed);
    }
    else
    {
        const char* sGravity = config.FirstChildElement("GAME_GRAVITY")->GetText();
        gravity = atof(sGravity);
        const char* sGameSpeed = config.FirstChildElement("GAME_INITIAL_SPEED")->GetText();
        gameSpeed = atof(sGameSpeed);
        const char* sGameSpeedDelta = config.FirstChildElement("GAME_SPEED_DELTA")->GetText();
        gameSpeedDelta = atof(sGameSpeedDelta);
        const char* sJumpingSpeed = config.FirstChildElement("JUMPING_SPEED")->GetText();
        jumpingSpeed = atof(sJumpingSpeed);
    }
}

void LoadHighScore()
{
    // Loading High score from previous attempts
    std::ifstream fHighScoreIn;
    char c;

    fHighScoreIn.open("highScore.bin", std::ifstream::in);
    if (!fHighScoreIn.good())
    {
        //TODO log failed to open highScore.bin, creating new file
        std::ofstream fHighScoreOut("highScore.bin", std::ofstream::out);
        if (!fHighScoreOut.good())
        {
            // TODO log failed to open file
        }
        else
        {
            fHighScoreOut << 0;
            fHighScoreOut.close();
        }
    }
    else
    {
        while (fHighScoreIn.get(c))
        {
            highScore *= 10;
            highScore += (c - 48);
        }
        fHighScoreIn.close();
    }
}

void WriteScore()
{
    // Write high score to file
    std::ofstream fHighScore("highScore.bin", std::ofstream::out);
    if (!fHighScore.good())
    {
        // TODO log failed to open or create highScore.bin
    }
    else
    {
        fHighScore << highScore;
        fHighScore.close();
    }
}

void UpdateHorizonLineGap()
{
    if (tRex->GetPositionY() == TREX_STARTING_POSITION_Y)
    {
        horizonLineGap.setFillColor(sf::Color::Black);
    }
    else
    {
        horizonLineGap.setFillColor(sf::Color::Transparent);
    }
}

void AddObstacle(std::vector<Obstacle*> obstaclesList)
{
    obstacleDistance = OBSTACLE_RESPAWN_BASE_DISTANCE + rand() % obstacleRespawnMaxDistance;
    if (obstacleDistance >= showPterodactyl)
    {
        obstacles.push_back(new Pterodactyl(obstacleDistance + lastDistance));
        lastDistance += obstacleDistance;
    }
    else
    {
        obstacles.push_back(new Cactus(obstacleDistance + lastDistance, rand() % 4 + 1));
        lastDistance += obstacleDistance;
    }
    numberOfVisibleObstacles++;
}

void UpdateAllObstacles()
{
    // Adding obstacles if needed
    while (numberOfVisibleObstacles < MAX_OBSTACLE_COUNT)
    {
        AddObstacle(obstacles);
    }
    for (auto it = obstacles.begin(); it != obstacles.end(); it++)
        (*it)->Move(gameSpeed);
    // clearing obstacles that passed the screen
    // TODO void ClearPassedObstacles(std::vector<GameObject*> obstacles)
    if (!obstacles.empty() && obstacles[0]->GetPositionX() < 0)
    {
        delete obstacles[0];
        obstacles.erase(obstacles.begin());
        numberOfVisibleObstacles--;
    }
    if (!obstacles.empty())
    {
        lastDistance = obstacles[obstacles.size() - 1]->GetPositionX();
    }
    else
    {
        lastDistance = WIDTH;
    }
    
}

bool CheckCollision(TRex* tRex, Obstacle* obstacle)
{
    if (tRex->Colliding(obstacle))
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

void GameOver()
{
    WriteScore();
    window.clear();
    tRex->Crash();
    tRex->Draw(&window);
    window.draw(highScoreText);
    window.draw(scoreText);
    window.draw(gameOverText);
    window.display();
}

void DeleteObstacles()
{
    while (!obstacles.empty())
    {
        delete obstacles[0];
        obstacles.erase(obstacles.begin());
    }
    numberOfVisibleObstacles = 0;
}

void HandlePeriodicIncrements(clock_t currentTime)
{
    if (currentTime - scoreTimer >= GAME_SCORE_INCREMENT)
    {
        scoreTimer = clock();
        score++;
        if (score % 100 == 0)
        {
            gameSpeed += gameSpeedDelta;
            obstacleRespawnBaseDistance += OBSTACLE_RESPAWN_DISTANCE_INC;
            obstacleRespawnMaxDistance += OBSTACLE_RESPAWN_DISTANCE_INC;
            showPterodactyl += OBSTACLE_RESPAWN_DISTANCE_INC;
        }
        if (score > highScore)
        {
            highScore = score;
        }
    }
}

void UpdateTextFields(int score, int highScore)
{
    highScoreText.setString("HI " + std::to_string(highScore));
    scoreText.setString(std::to_string(score));
}

void DrawEverything()
{
    window.clear();
    window.draw(highScoreText);
    window.draw(scoreText);
    window.draw(horizonLine);
    window.draw(horizonLineGap);
    horizonBump1->Draw(&window);
    horizonBump2->Draw(&window);
    if (!obstacles.empty())
    {
        for (auto it = obstacles.begin(); it != obstacles.end(); it++)
        {
            (*it)->Draw(&window);
        }
    }
    tRex->Draw(&window);
    // Displaying whats drawn
    window.display();
}

void MoveBumps()
{
    horizonBump1->Move(gameSpeed);
    horizonBump2->Move(gameSpeed);
}

void Game()
{
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
            UpdateHorizonLineGap();
            MoveBumps();
            
            // Removing obstacles that passed the screen
            // move/remove/updateSprites
            // handle lastDistance (distance of furthest obstacle)
            UpdateAllObstacles();
            
            // Checking if TRex collided with an obstacle
            if (CheckCollision(tRex, obstacles[0]) || firstFrame)
            {
                GameOver();
                DeleteObstacles();
                if (!(GetKeyState(VK_UP) & 0x8000) && !(GetKeyState(VK_DOWN) & 0x8000))
                {
                    keyPressed = false;
                }
                if ((GetKeyState(VK_UP) & 0x8000) && !keyPressed) // To not restart game while holding down the UP arrow key
                {
                    firstFrame = true;
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

                HandlePeriodicIncrements(clock());
            }

            UpdateTextFields(score, highScore);
            DrawEverything();

        }
    }
}


void RunGame()
{
    InitGame();
    Game();
    WriteScore();
}