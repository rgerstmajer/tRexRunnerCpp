#pragma once

#define WIDTH 256
#define HEIGHT 64


#define GRAVITY 1
#define GAME_SPEED 3

#define JUMPING_SPEED 2
#define TREX_MAX_HEIGHT 5
#define TREX_STARTING_POSITION_X 10
#define TREX_STARTING_POSITION_Y 40
#define TREX_DUCKING_POSITION_X 14
#define TREX_DUCKING_POSITION_Y 45



enum gameObjectType
{
    TREX,
    OBSTACLE,
    HORIZON
};