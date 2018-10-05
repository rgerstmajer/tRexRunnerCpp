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
  //!Game Objects
  TRex* tRex;
  Horizon* horizonBump1;
  Horizon* horizonBump2;
  std::vector <Obstacle*> obstacles;
  std::vector <Pterodactyl*> pterodactyls;

  //!Text resources
  sf::Font font;
  sf::Text scoreText;
  sf::Text highScoreText;
  sf::Text gameOverText;

  //!Horizon and gap for tRex padding
  sf::RectangleShape horizonLine;
  sf::RectangleShape horizonLineGap;

  //!Counters for obstacle spawn logic
  int numberOfVisibleObstacles = 0;
  int obstacleRespawnMaxDistance = WIDTH - OBSTACLE_RESPAWN_BASE_DISTANCE;
  int showPterodactyl = SHOW_PTERODACTYL;
  int obstacleDistance = 0;
  int obstacleRespawnBaseDistance = OBSTACLE_RESPAWN_BASE_DISTANCE;
  float lastDistance = WIDTH;

  //!Score and hogh score
  int highScore = 0;
  int score = 0;

  //!Global game logic variables
  bool firstFrame = false;
  bool keyPressed = false;
  bool gameOver = false;

  //!Timers for framerate, and score increments
  clock_t beginTime = clock();
  clock_t scoreTimer = clock();

  //!Configurable variables
  float gravity =        GAME_GRAVITY;
  float gameSpeed =      GAME_INITIAL_SPEED;
  float gameSpeedDelta = GAME_SPEED_DELTA;
  float jumpingSpeed =   JUMPING_SPEED;

  //!Display window
  sf::RenderWindow* window;

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
  void LoadTextFields();
  /*!
  * Loads config file
  */
  void LoadConfig();
  /*!
  * Loads previous high score
  */
  void LoadHighScore();
  /*!
  * Writes high score to file
  */
  void WriteScore();
  /*!
  * Updates horizon line gap to
  * make tRex appear in front
  */
  void UpdateHorizonLineGap();
  /*!
  * Updates all obstacles ( moving,
  * removing and changing sprites )
  */
  void UpdateAllObstacles();
  /*!
  * Adding an obstacle to
  * a vector
  * \param obstacles vector of obstacles
  */
  void AddObstacle(std::vector<Obstacle*> obstacles);
  /*!
  * Check if tRex is colliding with Obstacle
  * \param tRex
  * \param obstacle
  */
  bool CheckCollision(TRex* trex, Obstacle* obstacle);
  /*!
  * Displays Game Over screen
  */
  void GameOver();
  /*!
  * Remove all obstacles
  */
  void DeleteObstacles();
  /*!
  * Clear obstacles that left the screen
  */
  void ClearObstaclesThatPassed();
  /*!
  * Handles events that occur periodically
  */
  void HandlePeriodicIncrements();
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
  void MoveBumps();
  /*!
  * Handle button presses
  * \param upArrow bool value of wether the UpArrowKey is pressed
  * \param downArrow bool value of wether the DownArrowKey is pressed
  */
  void HandleButtonPress(bool upArrow, bool downArrow, bool isGameOver);

  bool IsButtonPressed(int arrow);
};