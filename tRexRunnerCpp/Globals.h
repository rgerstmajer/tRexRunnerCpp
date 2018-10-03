//! Globals.h
/*!
* Global variables used for tRexRunnerCpp
*
* Created: 20.08.2018.
* Author : Robert Gerstmajer
*/
#pragma once


#define BITS_IN_BYTE 8

#define GAME_SCALE 2
#define WHITE 255
#define BLACK 0

#define WIDTH 256
#define HEIGHT 64

#define RENDER_PERIOD 20 // 50 fps

#define GAME_GRAVITY     3.2f
#define GAME_INITIAL_SPEED 3.8f
#define GAME_SPEED_DELTA   0.4f
#define JUMPING_SPEED    3.5f
#define GAME_SCORE_INCREMENT 50

#define TREX_RUNNING_SPEED 2
#define TREX_MAX_HEIGHT 5
#define LIMB_CHANGE_COUNTER 15

#define HORIZON_POSITION_X 0
#define HORIZON_POSITION_Y 62
#define HORIZON_LENGTH WIDTH
#define HORIZON_WIDTH 1

#define MAX_OBSTACLE_COUNT 3
#define SHOW_PTERODACTYL 240
#define OBSTACLE_RESPAWN_BASE_DISTANCE  100
#define OBSTACLE_RESPAWN_DISTANCE_INC 10

//SPRITES

#define HORIZON_LINE_WIDTH      WIDTH
#define HORIZON_LINE_HEIGHT     2 * GAME_SCALE
#define HORIZON_LINE_BUMP1_X    40 * GAME_SCALE
#define HORIZON_LINE_BUMP1_WIDTH  4 * GAME_SCALE
#define HORIZON_LINE_BUMP2_X    105 * GAME_SCALE
#define HORIZON_LINE_BUMP2_WIDTH  6 * GAME_SCALE

#define TREX_PADDING_RIGHT      10 * GAME_SCALE
#define TREX_STANDING_CLEARENCE_MIN 2 * GAME_SCALE
#define TREX_STANDING_CLEARENCE_MAX 9 * GAME_SCALE
#define TREX_DUCKING_CLEARENCE_MIN  3 * GAME_SCALE
#define TREX_DUCKING_CLEARENCE_MAX  10 * GAME_SCALE


#define TREX_STANDING_WIDTH   14
#define TREX_STANDING_HEIGHT  14
static const unsigned char trex_standing_init[] =
{
  0xfc, 0xe0, 0xc0, 0xe0, 0xe0, 0xf0, 0xfe, 0xff, 0xfd, 0x5f, 0xd7, 0x17, 0x07, 0x06,
  0x01, 0x03, 0x07, 0x3f, 0x2f, 0x07, 0x3f, 0x23, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00
};
// width & height same as for trex_standing_init
static const unsigned char trex_running1[] =
{
  0xfc, 0xe0, 0xc0, 0xe0, 0xe0, 0xf0, 0xfe, 0xff, 0xfd, 0x5f, 0xd7, 0x17, 0x07, 0x06,
  0x01, 0x03, 0x07, 0x1f, 0x17, 0x07, 0x3f, 0x23, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00
};
// width & height same as for trex_standing_init
static const unsigned char trex_running2[] =
{
  0xfc, 0xe0, 0xc0, 0xe0, 0xe0, 0xf0, 0xfe, 0xff, 0xfd, 0x5f, 0xd7, 0x17, 0x07, 0x06,
  0x01, 0x03, 0x07, 0x3f, 0x2f, 0x07, 0x0f, 0x0b, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00
};
// width & height same as for trex_standing_init

static const unsigned char trex_dead[] =
{
  0xfc, 0xe0, 0xc0, 0xe0, 0xe0, 0xf0, 0xfe, 0xfb, 0xf5, 0x5b, 0xd7, 0x17, 0x07, 0x06,
  0x01, 0x03, 0x07, 0x3f, 0x2f, 0x07, 0x3f, 0x23, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00
};

#define TREX_DUCKING_WIDTH  22
#define TREX_DUCKING_HEIGHT 9
#define TREX_STARTING_POSITION_X 10
#define TREX_STARTING_POSITION_Y HEIGHT - TREX_STANDING_HEIGHT * GAME_SCALE - 1
#define TREX_DUCKING_POSITION_X TREX_STARTING_POSITION_X
#define TREX_DUCKING_POSITION_Y HEIGHT - TREX_DUCKING_HEIGHT * GAME_SCALE - 1
static const unsigned char trex_ducking1[] =
{
  0x03, 0x06, 0x0e, 0x1c, 0xfc, 0x7c, 0x3e, 0x1e, 0x7e, 0x5e, 0x1e, 0x7e, 0x5c, 0x0c, 0x1e, 0x1d, 0x1f, 0x1f, 0x17, 0x17, 0x07, 0x06,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static const unsigned char trex_ducking2[] =
{
  0x03, 0x06, 0x0e, 0x1c, 0x7c, 0x5c, 0x3e, 0xfe, 0x7e, 0x7e, 0x1e, 0x7e, 0x5c, 0x0c, 0x1e, 0x1d, 0x1f, 0x1f, 0x17, 0x17, 0x07, 0x06,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};



#define PTERODACTYL_WIDTH   11
#define PTERODACTYL_HEIGHT  10
static const unsigned char pterodactyl1[] =
{
  0x10, 0x18, 0x1c, 0x30, 0x7f, 0xfe, 0xfc, 0xf8, 0xa0, 0xa0, 0x20,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static const unsigned char pterodactyl2[] =
{
  0x10, 0x18, 0x1c, 0x3c, 0xf0, 0xf0, 0xf0, 0xf0, 0xa0, 0xa0, 0x20,
  0x00, 0x00, 0x00, 0x00, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00
};

#define CACTUS_PADDING_BOTTOM     2
#define CACTUS_NUMBER_OF_SPECIES  4

#define CACTUS1_WIDTH   5
#define CACTUS1_HEIGHT  8
static const unsigned char cactus1[] =
{
  0x1c, 0x10, 0xfe, 0x20, 0x3c
};

#define CACTUS2_WIDTH   5
#define CACTUS2_HEIGHT  8
static const unsigned char cactus2[] =
{
  0x0c, 0x08, 0xff, 0x10, 0x1c
};

#define CACTUS3_WIDTH   6
#define CACTUS3_HEIGHT  9
static const unsigned char cactus3[] =
{
  0x0e, 0x08, 0xfe, 0xff, 0x20, 0x38,
  0x00, 0x00, 0x01, 0x01, 0x00, 0x00
};

#define CACTUS4_WIDTH   11
#define CACTUS4_HEIGHT  7
static const unsigned char cactus4[] =
{
  0x0c, 0x08, 0x7e, 0x10, 0x1c, 0x00, 0x0e, 0x08, 0x7f, 0x10, 0x1c
};

#define BUMP1_WIDTH   4
#define BUMP1_HEIGHT  2
static const unsigned char bump1[] =
{
  0x01,0x01,0x01,0x01
};

#define BUMP2_WIDTH   6
#define BUMP2_HEIGHT  2
static const unsigned char bump2[] =
{
  0x01,0x01,0x01,0x01,0x01,0x01
};