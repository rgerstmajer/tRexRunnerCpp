#include "Game.h"

Game::Game(sf::RenderWindow* renderWindow)
{
  window = renderWindow;
  horizonLine = sf::RectangleShape(sf::Vector2f(HORIZON_LENGTH, HORIZON_WIDTH));
  horizonLineGap = sf::RectangleShape(sf::Vector2f(TREX_STANDING_WIDTH, HORIZON_WIDTH * GAME_SCALE));
}

void Game::RunGame()
{
  LoadTextFields();
  InitGame();
  GameLogic();
  if (!gameOver)
  {
    GameOver();
  }
  WriteScore();
}

void Game::InitGame()
{
  horizonLineGap.setPosition(TREX_STARTING_POSITION_X + TREX_STANDING_WIDTH / 3, HORIZON_POSITION_Y - 1);
  horizonLine.setPosition(HORIZON_POSITION_X, HORIZON_POSITION_Y);
  score = 0;
  highScore = 0;
  gameOver = false;
  numberOfVisibleObstacles = 0;
  LoadConfig();
  LoadHighScore();
  tRex = new TRex(jumpingSpeed, gravity);
  horizonBump1 = new Horizon(1);
  horizonBump2 = new Horizon(2);
}

void Game::GameLogic()
{
  while (window->isOpen())
  {
    // Execute only when render period is met
    if (((clock() - beginTime)) >= RENDER_PERIOD)
    {
      beginTime = clock();
      srand(beginTime);
      sf::Event event;
      while (window->pollEvent(event))
      {
        if (event.type == sf::Event::Closed)
          window->close();
      }
      // Checking if TRex collided with an obstacle
      if (!obstacles.empty() && CheckCollision(tRex, obstacles[0]) || gameOver)
      {
        if (!gameOver)
        {
          GameOver();
          DeleteObstacles();
        }
        HandleButtonPress(IsButtonPressed(UP), IsButtonPressed(DOWN), gameOver);
      }
      // If not colliding with anything, continue
      else
      {
        HandleButtonPress(IsButtonPressed(UP), IsButtonPressed(DOWN), gameOver);
        UpdateHorizonLineGap();
        MoveBumps(horizonBump1, horizonBump2);
        UpdateAllObstacles();
        HandlePeriodicIncrements();
        UpdateTextFields(score, highScore);
        DrawEverything();
      }
    }
  }
}

void Game::LoadTextFields()
{
  if (!font.loadFromFile("Minecraft.ttf"))
  {
    printf("Cannot load font file");
    window->close();
  }
  else
  {
    scoreText.setFont(font);
    highScoreText.setFont(font);
    gameOverText.setFont(font);
    scoreText.setCharacterSize(12);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(WIDTH / 2, 0);
    highScoreText.setCharacterSize(12);
    highScoreText.setFillColor(sf::Color::White);
    highScoreText.setPosition(0, 0);
    gameOverText.setCharacterSize(15);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setString("GAME OVER");
    gameOverText.setPosition(WIDTH / 3, HEIGHT / 3);
  }
}

void Game::LoadConfig()
{
  // Reading the game config file
  tinyxml2::XMLDocument config;
  tinyxml2::XMLError pError = config.LoadFile("tRexRunnerConfig.xml");
  if (pError != 0)
  {
    printf("Config file not found, using defaults:\nGravity: %.2f\nGameSpeed: %.2f\nGameSpeedDelta: %.2f\nJumpingSpeed: %.2f\n", gravity, gameSpeed, gameSpeedDelta, jumpingSpeed);
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

void Game::LoadHighScore()
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

void Game::WriteScore()
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

void Game::UpdateHorizonLineGap()
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

void Game::UpdateAllObstacles()
{
  // Adding obstacles if needed
  while (numberOfVisibleObstacles < MAX_OBSTACLE_COUNT)
  {
    AddObstacle(obstacles);
  }
  for (auto it = obstacles.begin(); it != obstacles.end(); it++)
    (*it)->Update(gameSpeed);
  // clearing obstacles that passed the screen
  ClearObstaclesThatPassed();
  if (!obstacles.empty())
  {
    lastDistance = obstacles[obstacles.size() - 1]->GetPositionX();
  }
  else
  {
    lastDistance = WIDTH;
  }
  
}

void Game::AddObstacle(std::vector<Obstacle*> obstaclesList)
{
  obstacleDistance = OBSTACLE_RESPAWN_BASE_DISTANCE + rand() % obstacleRespawnMaxDistance;
  if (obstacleDistance >= showPterodactyl)
  {
    obstacles.push_back(new Pterodactyl(obstacleDistance + lastDistance));
    lastDistance += obstacleDistance;
  }
  else
  {
    obstacles.push_back(new Cactus(obstacleDistance + lastDistance + WIDTH / 4, rand() % 4 + 1));
    lastDistance += obstacleDistance;
  }
  numberOfVisibleObstacles++;
}

bool Game::CheckCollision(TRex* tRex, Obstacle* obstacle)
{
  if (!obstacles.empty())
  {
    return tRex->Colliding(obstacle);
  }
  else
  {
    return false;
  }
}

void Game::GameOver()
{
  gameOver = true;
  WriteScore();
  window->clear();
  tRex->Crash();
  tRex->Draw(window);
  window->draw(highScoreText);
  window->draw(scoreText);
  window->draw(gameOverText);
  window->display();
  delete(tRex);
  delete(horizonBump1);
  delete(horizonBump2);
}

void Game::ClearObstaclesThatPassed()
{
  if (!obstacles.empty() && obstacles[0]->GetPositionX() < 0)
  {
    delete obstacles[0];
    obstacles.erase(obstacles.begin());
    numberOfVisibleObstacles--;
  }
}

void Game::DeleteObstacles()
{
  while (!obstacles.empty())
  {
    delete obstacles[0];
    obstacles.erase(obstacles.begin());
  }
  numberOfVisibleObstacles = 0;
}

void Game::HandlePeriodicIncrements()
{
  if (clock() - scoreTimer >= GAME_SCORE_INCREMENT)
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

void Game::UpdateTextFields(int score, int highScore)
{
  highScoreText.setString("HI " + std::to_string(highScore));
  scoreText.setString(std::to_string(score));
}

void Game::DrawEverything()
{
  window->clear();
  window->draw(highScoreText);
  window->draw(scoreText);
  window->draw(horizonLine);
  window->draw(horizonLineGap);
  horizonBump1->Draw(window);
  horizonBump2->Draw(window);
  if (!obstacles.empty())
  {
    for (auto it = obstacles.begin(); it != obstacles.end(); it++)
    {
      (*it)->Draw(window);
    }
  }
  tRex->Draw(window);
  window->display();
}

void Game::MoveBumps(Horizon* bump1, Horizon* bump2)
{
  bump1->Move(gameSpeed);
  bump2->Move(gameSpeed);
}

void Game::HandleButtonPress(bool upArrow, bool downArrow, bool isGameOver)
{
  switch (isGameOver)
  {
  case true:
    if (!upArrow && !downArrow)
    {
      keyPressed = false;
    }
    if (upArrow && !keyPressed) // To not restart game while holding down the UP arrow key
    {
      InitGame();
    }
    break;
  case false:
    if (upArrow)
    {
      keyPressed = true;
      tRex->Jump();
    }
    else if (downArrow)
    {
      keyPressed = true;
      tRex->Duck();
    }
    else
    {
      keyPressed = false;
      tRex->Run();
    }
    break;
  }
}

bool Game::IsButtonPressed(int arrow)
{
  switch (arrow)
  {
  case 0:
    return (GetKeyState(VK_UP) & 0x8000);
  case 1:
    return (GetKeyState(VK_DOWN) & 0x8000);
  default:
    return false;
  }
}
