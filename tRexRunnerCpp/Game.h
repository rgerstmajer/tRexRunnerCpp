#pragma once

#include "TRex.h"
#include "Cactus.h"
#include "Pterodactyl.h"
#include "Horizon.h"
#include "Globals.h"

#include <windows.h>
#include <ctime>
#include <math.h>


bool Colliding();
void RunGame();
void InitGame();
void Run();

struct pixel {
    unsigned char r = 255;
    unsigned char g = 255;
    unsigned char b = 255;
    unsigned char a;
};


