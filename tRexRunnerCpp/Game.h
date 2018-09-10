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

static TRex* tRex;
static Horizon* horizonBump1;
static Horizon* horizonBump2;
static Pterodactyl* pterodactyl;
static std::vector <Cactus*> obstacles;
static std::vector <Pterodactyl*> pterodactyls;
static sf::Font font;
static sf::Text scoreText;
static sf::Text highScoreText;
static sf::Text gameOverText;

static int numberOfVisibleObstacles;
static int obstacleRespawnMaxDistance = WIDTH - OBSTACLE_RESPAWN_BASE_DISTANCE;
static int showPterodactyl = SHOW_PTERODACTYL;

static int HighScore = 0;
static int Score = 0;
static int obstacleDistance = 0;
static int obstacleRespawnBaseDistance = OBSTACLE_RESPAWN_BASE_DISTANCE;
static float lastDistance = 0;
static bool pterodactylPresent = false;
static bool firstFrame = false;
static bool keyPressed = false;

static clock_t beginTime = clock();
static clock_t scoreTimer = clock();

static float Gravity = GAME_GRAVITY;
static float GameSpeed = GAME_INITIAL_SPEED;
static float GameSpeedDelta = GAME_SPEED_DELTA;
static float JumpingSpeed = JUMPING_SPEED;

void RunGame();
void InitGame();
void LoadTextFields();
void LoadConfig();
void LoadHighScore();
void WriteScore();
void Game();
