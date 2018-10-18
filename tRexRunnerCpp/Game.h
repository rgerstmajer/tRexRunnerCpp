//! Game.h
/*!
* Game class header file
*
* Created: 20.08.2018.
* Author : Robert Gerstmajer
*/
#pragma once

#include "TRex.h"
#include "Cactus.h"
#include "Pterodactyl.h"
#include "Horizon.h"
#include "Globals.h"
#include "tinyxml2.h"

#include <vld.h>
#include <windows.h>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <math.h>
#include <algorithm>
#include <vector>
#include <fstream>
class Game
{
public:
  /*!
  * Constructor
  */
  Game(sf::RenderWindow* renderWindow);
  /*!
  * Runs game
  */
  void RunGame();
  /*!
  * Initializes tRex and horizon
  */
  void InitGame();
  /*!
  * Runs game logic
  */
  void GameLogic();
  /*!
  * Loads sfml text for scores
  */
  void LoadTextFields(const char* fileName);
  /*!
  * Loads config file
  */
  void LoadConfig(const char* fileName);
  /*!
  * Loads previous high score
  */
  void LoadHighScore(const char* fileName);
  /*!
  * Writes high score to file
  */
  void WriteScore(const char* fileName);
  /*!
  * Updates horizon line gap to
  * make tRex appear in front
  */
  void UpdateHorizonLineGap();
  /*!
  * Updates all obstacles ( moving,
  * removing and changing sprites )
  */
  void UpdateAllObstacles(std::vector<Obstacle*>* obstacleList);
  /*!
  * Adding an obstacle to
  * a vector
  * \param obstacles vector of obstacles
  */
  void AddObstacle(std::vector<Obstacle*>* obstacles);
  /*!
  * Check if tRex is colliding with Obstacle
  * \param tRex
  * \param obstacle
  */
  bool CheckCollision(TRex* trex, std::vector<Obstacle*>* obstacle);
  /*!
  * Displays Game Over screen
  */
  void GameOver(Game* currentGame);
  /*!
  * Remove all obstacles
  */
  void DeleteObstacles(std::vector<Obstacle*>* obstacleList);
  /*!
  * Clear obstacles that left the screen
  */
  void ClearObstaclesThatPassed(std::vector<Obstacle*>* obstacleList);
  /*!
  * Handles events that occur periodically
  */
  void HandlePeriodicIncrements(clock_t currentTime);
  /*!
  * Updates text fields
  */
  void UpdateTextFields(int score, int highScore);
  /*!
  * Draws all elements present
  */
  void DrawEverything();
  /*!
  * Moves horizon bumps
  */
  void MoveBumps(Horizon* bump1, Horizon* bump2);
  /*!
  * Handle button presses
  * \param upArrow bool value of wether the UpArrowKey is pressed
  * \param downArrow bool value of wether the DownArrowKey is pressed
  */
  void HandleButtonPress(bool upArrow, bool downArrow, bool isGameOver);
  /*!
  * Checks wether a key is pressed
  * \param int arrow (0 for UP, 1 for DOWN)
  */
  bool IsButtonPressed(int arrow);

  int  GetScore() { return score; };
  int  GetHighScore() { return highScore; };
  void SetScore(int newScore) { score = newScore; };

protected:
  //!Game Objects
  TRex*    tRex         = NULL;
  Horizon* horizonBump1 = NULL;
  Horizon* horizonBump2 = NULL;
  std::vector <Obstacle*> obstacles;
  std::vector <Pterodactyl*> pterodactyls;

  //!Text resources
  sf::Font font;
  sf::Text scoreText;
  sf::Text highScoreText;
  sf::Text gameOverText;

  //!Horizon and gap for tRex padding
  sf::RectangleShape horizonLine = sf::RectangleShape(sf::Vector2f(0,0));
  sf::RectangleShape horizonLineGap = sf::RectangleShape();

  //!Counters for obstacle spawn logic
  int numberOfVisibleObstacles    = 0;
  int obstacleDistance            = 0;
  int obstacleRespawnMaxDistance  = WIDTH - OBSTACLE_RESPAWN_BASE_DISTANCE;
  int showPterodactyl             = SHOW_PTERODACTYL;
  int obstacleRespawnBaseDistance = OBSTACLE_RESPAWN_BASE_DISTANCE;
  float lastDistance              = WIDTH;

  //!Score and high score
  int highScore = 0;
  int score     = 0;

  //!Global game logic variables
  bool firstFrame = false;
  bool keyPressed = false;
  bool gameOver   = false;

  //!Timers for framerate, and score increments
  clock_t beginTime  = clock();
  clock_t scoreTimer = clock();

  //!Configurable variables
  float gravity         = GAME_GRAVITY;
  float gameSpeed       = GAME_INITIAL_SPEED;
  float gameSpeedDelta  = GAME_SPEED_DELTA;
  float jumpingSpeed    = JUMPING_SPEED;

  //!Display window
  sf::RenderWindow* window = NULL;
};
