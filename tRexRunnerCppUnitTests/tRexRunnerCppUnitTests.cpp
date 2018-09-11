// tRexRunnerCppUnitTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <Game.h>

TRex* testTRex = new TRex(5.0,5.0);
Pterodactyl* testPterodactyl = new Pterodactyl();
Cactus* testCactus = new Cactus();

TEST_CASE("My First Test")
{
    REQUIRE(testTRex->GetPositionX() == TREX_STARTING_POSITION_X);
}

TEST_CASE("Jumping speed test")
{
    testTRex->Jump();
    REQUIRE(testTRex->GetPositionY() == TREX_STARTING_POSITION_Y - 5);
}

TEST_CASE("Dropping speed test")
{
    while (testTRex->GetPositionY() != TREX_MAX_HEIGHT)
    {
        testTRex->Jump();
    }
    testTRex->Jump();
    REQUIRE(testTRex->GetPositionY() == TREX_MAX_HEIGHT + 5);
}

TEST_CASE("Obstacle moving speed test")
{
    testPterodactyl->Init(10);
    testPterodactyl->Move(3);
    REQUIRE(testPterodactyl->GetPositionX() == 7);
    testCactus->Init(10, 1);
    float cactusInitPositionX = testCactus->GetPositionX();
    testCactus->Move(3);
    REQUIRE(testCactus->GetPositionX() == cactusInitPositionX - 3);
}