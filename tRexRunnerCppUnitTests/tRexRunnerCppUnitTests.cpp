// tRexRunnerCppUnitTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <Game.h>

TRex* testTRex = new TRex(5.0,5.0);

TEST_CASE("When creating TRex, initial position should be TREX_STARTING_POSITION_X and TREX_STARTING_POSITION_Y")
{
    REQUIRE(testTRex->GetPositionY() == TREX_STARTING_POSITION_Y);
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