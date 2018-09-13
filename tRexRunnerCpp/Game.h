//! Game.h
/*!
* Game header file
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

//#include <vld.h>
#include <windows.h>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <math.h>
#include <algorithm>
#include <vector>
#include <fstream>

static TRex* tRex;
static Horizon* horizonBump1;
static Horizon* horizonBump2;
static std::vector <Obstacle*> obstacles;
static std::vector <Pterodactyl*> pterodactyls;
static sf::Font font;
static sf::Text scoreText;
static sf::Text highScoreText;
static sf::Text gameOverText;
static sf::RectangleShape horizonLine((sf::Vector2f(HORIZON_LENGTH, HORIZON_WIDTH)));
static sf::RectangleShape horizonLineGap(sf::Vector2f(TREX_STANDING_WIDTH, HORIZON_WIDTH * 2));

static int numberOfVisibleObstacles = 0;
static int obstacleRespawnMaxDistance = WIDTH - OBSTACLE_RESPAWN_BASE_DISTANCE;
static int showPterodactyl = SHOW_PTERODACTYL;

static int highScore = 0;
static int score = 0;
static int obstacleDistance = 0;
static int obstacleRespawnBaseDistance = OBSTACLE_RESPAWN_BASE_DISTANCE;
static float lastDistance = WIDTH;
static bool pterodactylPresent = false;
static bool firstFrame = false;
static bool keyPressed = false;

static clock_t beginTime = clock();
static clock_t scoreTimer = clock();

//Configurable variables
static float gravity = GAME_GRAVITY;
static float gameSpeed = GAME_INITIAL_SPEED;
static float gameSpeedDelta = GAME_SPEED_DELTA;
static float jumpingSpeed = JUMPING_SPEED;
/*!
* Runs game
*/
void RunGame();
/*!
* Initializes tRex and horizon
*/
void InitGame();
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
* Runs game logic
*/
void Game();
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
bool CheckCollision(TRex* tRex, Obstacle* obstacle);
/*!
* Displays Game Over screen
*/
void GameOver();
/*!
* Remove all obstacles
*/
void DeleteObstacles();