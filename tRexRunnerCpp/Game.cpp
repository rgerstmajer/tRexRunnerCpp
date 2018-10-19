#include "Game.h"

Game::Game(sf::RenderWindow* renderWindow)
{
  m_window = renderWindow;
  m_horizonLine = sf::RectangleShape(sf::Vector2f(HORIZON_LENGTH, HORIZON_WIDTH));
  m_horizonLineGap = sf::RectangleShape(sf::Vector2f(TREX_STANDING_WIDTH, HORIZON_WIDTH * GAME_SCALE));
}

void Game::RunGame()
{
  LoadTextFields(FONT_FILE_NAME);
  InitGame();
  GameLogic();
  if (!m_gameOver)
  {
    GameOver(this);
  }
  WriteScore(HIGH_SCORE_FILE_NAME);
}

void Game::InitGame()
{
  m_horizonLineGap.setPosition(TREX_STARTING_POSITION_X + TREX_STANDING_WIDTH / 3, HORIZON_POSITION_Y - 1);
  m_horizonLine.setPosition(HORIZON_POSITION_X, HORIZON_POSITION_Y);
  m_score = 0;
  m_highScore = 0;
  m_gameOver = false;
  m_numberOfVisibleObstacles = 0;
  LoadConfig(CONFIG_FILE_NAME);
  LoadHighScore(HIGH_SCORE_FILE_NAME);
  m_tRex = new TRex(m_jumpingSpeed, m_gravity);
  m_horizonBump1 = new Horizon(1);
  m_horizonBump2 = new Horizon(2);
  if (m_tRex == NULL || m_horizonBump1 == NULL || m_horizonBump2 == NULL)
    m_window->close();
}

void Game::GameLogic()
{
  while (m_window->isOpen())
  {
    // Execute only when render period is met
    if (((clock() - m_beginTime)) >= RENDER_PERIOD)
    {
      m_beginTime = clock();
      srand(m_beginTime);
      sf::Event event;
      while (m_window->pollEvent(event))
      {
        if (event.type == sf::Event::Closed)
          m_window->close();
      }
      // Checking if TRex collided with an obstacle
      if (!m_obstacles.empty() && CheckCollision(m_tRex, &m_obstacles) || m_gameOver)
      {
        if (!m_gameOver)
        {
          GameOver(this);
          DeleteObstacles(&m_obstacles);
        }
        HandleButtonPress(IsButtonPressed(UP), IsButtonPressed(DOWN), m_gameOver, m_tRex);
      }
      // If not colliding with anything, continue
      else
      {
        HandleButtonPress(IsButtonPressed(UP), IsButtonPressed(DOWN), m_gameOver, m_tRex);
        UpdateHorizonLineGap();
        MoveBumps(m_horizonBump1, m_horizonBump2, m_gameSpeed);
        UpdateAllObstacles(&m_obstacles);
        HandlePeriodicIncrements(clock());
        UpdateTextFields(m_score, m_highScore);
        DrawEverything();
      }
    }
  }
}

void Game::LoadTextFields(const char* fileName)
{
  if (!m_font.loadFromFile(fileName))
  {
    printf("Cannot load font file");
    m_window->close();
  }
  else
  {
    m_scoreText.setFont(m_font);
    m_highScoreText.setFont(m_font);
    m_gameOverText.setFont(m_font);
    m_scoreText.setCharacterSize(12);
    m_scoreText.setFillColor(sf::Color::White);
    m_scoreText.setPosition(WIDTH / 2, 0);
    m_highScoreText.setCharacterSize(12);
    m_highScoreText.setFillColor(sf::Color::White);
    m_highScoreText.setPosition(0, 0);
    m_gameOverText.setCharacterSize(15);
    m_gameOverText.setFillColor(sf::Color::White);
    m_gameOverText.setString("GAME OVER");
    m_gameOverText.setPosition(WIDTH / 3, HEIGHT / 3);
  }
}

void Game::LoadConfig(const char* fileName)
{
  // Reading the game config file
  tinyxml2::XMLDocument config;
  tinyxml2::XMLError pError = config.LoadFile(fileName);
  if (pError != 0)
  {
    printf("Config file not found, using defaults:\nGravity: %.2f\nGameSpeed: %.2f\nGameSpeedDelta: %.2f\nJumpingSpeed: %.2f\n", m_gravity, m_gameSpeed, m_gameSpeedDelta, m_jumpingSpeed);
  }
  else
  {
    const char* sGravity = config.FirstChildElement("GAME_GRAVITY")->GetText();
    m_gravity = atof(sGravity);
    const char* sGameSpeed = config.FirstChildElement("GAME_INITIAL_SPEED")->GetText();
    m_gameSpeed = atof(sGameSpeed);
    const char* sGameSpeedDelta = config.FirstChildElement("GAME_SPEED_DELTA")->GetText();
    m_gameSpeedDelta = atof(sGameSpeedDelta);
    const char* sJumpingSpeed = config.FirstChildElement("JUMPING_SPEED")->GetText();
    m_jumpingSpeed = atof(sJumpingSpeed);
  }
}

void Game::LoadHighScore(const char* fileName)
{
  // Loading High score from previous attempts
  std::ifstream fHighScoreIn;
  char c;

  fHighScoreIn.open(fileName, std::ifstream::in);
  if (!fHighScoreIn.good())
  {
    printf("Failed to open highScore.bin, creating new file");
    std::ofstream fHighScoreOut(fileName, std::ofstream::out);
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
      m_highScore *= 10;
      m_highScore += (c - 48);
    }
    fHighScoreIn.close();
  }
}

void Game::WriteScore(const char* fileName)
{
  // Write high score to file
  std::ofstream fHighScore(fileName, std::ofstream::out);
  if (!fHighScore.good())
  {
    printf("Failed to open HighScore.bin");
  }
  else
  {
    fHighScore << m_highScore;
    fHighScore.close();
  }
}

void Game::UpdateHorizonLineGap()
{
  if (m_tRex->GetPositionY() == TREX_STARTING_POSITION_Y)
  {
    m_horizonLineGap.setFillColor(sf::Color::Black);
  }
  else
  {
    m_horizonLineGap.setFillColor(sf::Color::Transparent);
  }
}

void Game::UpdateAllObstacles(std::vector<Obstacle*>* obstacleList)
{
  // clearing obstacles that passed the screen
  ClearObstaclesThatPassed(obstacleList);
  // Adding obstacles if needed
  while (m_numberOfVisibleObstacles < MAX_OBSTACLE_COUNT)
  {
    AddObstacle(obstacleList);
  }
  for (auto it = obstacleList->begin(); it != obstacleList->end(); it++)
    (*it)->Update(m_gameSpeed);
  if (!obstacleList->empty())
  {
    m_lastDistance = (*obstacleList)[obstacleList->size() - 1]->GetPositionX();
  }
  else
  {
    m_lastDistance = WIDTH;
  }
}

void Game::AddObstacle(std::vector<Obstacle*>* obstacleList)
{
  m_obstacleDistance = OBSTACLE_RESPAWN_BASE_DISTANCE + rand() % m_obstacleRespawnMaxDistance;
  try {
    if (m_obstacleDistance >= m_showPterodactyl)
    {
      obstacleList->push_back(new Pterodactyl(m_obstacleDistance + m_lastDistance));
      m_lastDistance += m_obstacleDistance;
    }
    else
    {
      obstacleList->push_back(new Cactus(m_obstacleDistance + m_lastDistance + WIDTH / 4, rand() % 4 + 1));
      m_lastDistance += m_obstacleDistance;
    }
    m_numberOfVisibleObstacles++;
  }
  catch (...)
  {
    printf("Failed to add obstacles");
    m_window->close();
  }
}

bool Game::CheckCollision(TRex* tRex, std::vector<Obstacle*>* obstacleList)
{
  if (!obstacleList->empty())
  {
    try
    {
      return tRex->Colliding((*obstacleList)[0]);
    }
    catch (...)
    {
      printf("Failed to check obstacleList for collision.");
      m_window->close();
    }
  }
  else
  {
    return false;
  }
}

void Game::GameOver(Game* currentGame)
{
  currentGame->m_gameOver = true;
  currentGame->WriteScore(HIGH_SCORE_FILE_NAME);
  currentGame->m_window->clear();
  currentGame->m_tRex->Crash();
  currentGame->m_tRex->Draw(m_window);
  currentGame->m_window->draw(m_highScoreText);
  currentGame->m_window->draw(m_scoreText);
  currentGame->m_window->draw(m_gameOverText);
  currentGame->m_window->display();
  DELETE_PTR(currentGame->m_tRex);
  DELETE_PTR(currentGame->m_horizonBump1);
  DELETE_PTR(currentGame->m_horizonBump2);
}

void Game::ClearObstaclesThatPassed(std::vector<Obstacle*>* obstacleList)
{
  if (!obstacleList->empty() && (*obstacleList)[0]->GetPositionX() < 0)
  {
    DELETE_PTR((*obstacleList)[0]);
    obstacleList->erase(obstacleList->begin());
    m_numberOfVisibleObstacles--;
  }
}

void Game::DeleteObstacles(std::vector<Obstacle*>* obstacleList)
{
  while (!obstacleList->empty())
  {
    DELETE_PTR((*obstacleList)[0]);
    obstacleList->erase(obstacleList->begin());
  }
  m_numberOfVisibleObstacles = 0;
}

void Game::HandlePeriodicIncrements(clock_t currentTime)
{
  if (currentTime - m_scoreTimer >= GAME_SCORE_INCREMENT)
  {
    m_scoreTimer = currentTime;
    m_score++;
    if (m_score % 100 == 0)
    {
      m_gameSpeed += m_gameSpeedDelta;
      m_obstacleRespawnBaseDistance += OBSTACLE_RESPAWN_DISTANCE_INC;
      m_obstacleRespawnMaxDistance += OBSTACLE_RESPAWN_DISTANCE_INC;
      m_showPterodactyl += OBSTACLE_RESPAWN_DISTANCE_INC;
    }
    if (m_score > m_highScore)
    {
      m_highScore = m_score;
    }
  }
}

void Game::UpdateTextFields(int score, int highScore)
{
  m_highScoreText.setString("HI " + std::to_string(highScore));
  m_scoreText.setString(std::to_string(score));
}

void Game::DrawEverything()
{
  m_window->clear();
  m_window->draw(m_highScoreText);
  m_window->draw(m_scoreText);
  m_window->draw(m_horizonLine);
  m_window->draw(m_horizonLineGap);
  m_horizonBump1->Draw(m_window);
  m_horizonBump2->Draw(m_window);
  if (!m_obstacles.empty())
  {
    for (auto it = m_obstacles.begin(); it != m_obstacles.end(); it++)
    {
      (*it)->Draw(m_window);
    }
  }
  m_tRex->Draw(m_window);
  m_window->display();
}

void Game::MoveBumps(Horizon* bump1, Horizon* bump2, float currentGameSpeed)
{
  bump1->Move(currentGameSpeed);
  bump2->Move(currentGameSpeed);
}

void Game::HandleButtonPress(bool upArrow, bool downArrow, bool isGameOver, TRex* tRex)
{
  switch (isGameOver)
  {
  case true:
    if (!upArrow && !downArrow)
    {
      m_keyPressed = false;
    }
    if (upArrow && !m_keyPressed) // To not restart game while holding down the UP arrow key
    {
      InitGame();
    }
    break;
  case false:
    if (upArrow)
    {
      m_keyPressed = true;
      tRex->Jump();
    }
    else if (downArrow)
    {
      m_keyPressed = true;
      tRex->Duck();
    }
    else
    {
      m_keyPressed = false;
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
