// tRexRunnerCppUnitTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <Game.h>

//TREX

TEST_CASE("When creating TRex, initial position should be TREX_STARTING_POSITION_X and TREX_STARTING_POSITION_Y")
{
  TRex testTRex(5.0,5.0);
  CHECK(testTRex.GetPositionY() == TREX_STARTING_POSITION_Y);
  REQUIRE(testTRex.GetPositionX() == TREX_STARTING_POSITION_X);
}

TEST_CASE("When jumping, TRex sprite should move up by \"jumping speed\" pixels")
{
  TRex testTRex(5.0, 5.0);
  testTRex.Jump();
  CHECK(testTRex.state == TRex::JUMPING);
  REQUIRE(testTRex.GetPositionY() == TREX_STARTING_POSITION_Y - 5);
}

TEST_CASE("When falling, TRex sprite should move down by \"gravity\" pixels")
{
  TRex testTRex(5.0, 5.0);
  while (testTRex.GetPositionY() != TREX_MAX_HEIGHT)
  {
    testTRex.Jump();
  }
  testTRex.Jump();
  REQUIRE(testTRex.GetPositionY() == TREX_MAX_HEIGHT + 5);
}

TEST_CASE("TRex Update method should switch state from STANDING to RUNNING1")
{
  TRex testTRex(5.0, 5.0);
  testTRex.Update();
  REQUIRE(testTRex.state == TRex::RUNNING1);
}

TEST_CASE("TRex Update method should not switch states if jumping")
{
  TRex testTRex(5.0, 5.0);
  testTRex.Jump();
  TRex::TRexStates initialState = testTRex.state;
  testTRex.Update();
  REQUIRE(testTRex.state == initialState);
}

TEST_CASE("TRex Run method should not switch states if jumping")
{
  TRex testTRex(5.0, 5.0);
  testTRex.Jump();
  TRex::TRexStates initialState = testTRex.state;
  testTRex.Run();
  REQUIRE(testTRex.state == initialState);
}

TEST_CASE("TRex Run method should switch state to RUNNING1 if TRex is not jumping ")
{
  TRex testTRex(5.0, 5.0);
  TRex::TRexStates initialState = testTRex.state;
  testTRex.Run();
  CHECK(testTRex.state == TRex::RUNNING1);
  testTRex.Duck();
  testTRex.Run();
  CHECK(testTRex.state == TRex::RUNNING1);
  testTRex.Jump();
  testTRex.Run();
  CHECK_FALSE(testTRex.state == TRex::RUNNING1);
}

TEST_CASE("TRex Run method should not switch states if running")
{
  TRex testTRex(5.0, 5.0);
  testTRex.Update();
  TRex::TRexStates initialState = testTRex.state;
  testTRex.Run();
  REQUIRE(testTRex.state == initialState);
}

TEST_CASE("TRex should change from RUNNING1 to RUNNING2 after LIMB_CHANGE_COUNTER frames")
{
  TRex testTRex(5.0, 5.0);
  for (int i = 0; i < LIMB_CHANGE_COUNTER; i++)
  {
    testTRex.Update();
  }
  REQUIRE(testTRex.state == TRex::RUNNING2);
}

TEST_CASE("TRex should change position when ducking to TREX_DUCKING_POSITION_X and TREX_DUCKING_POSITION_Y")
{
  TRex testTRex(5.0, 5.0);
  testTRex.Duck();
  CHECK(testTRex.GetPositionX() == TREX_DUCKING_POSITION_X);
  CHECK(testTRex.GetPositionY() == TREX_DUCKING_POSITION_Y);
}

//PTERODACTYL

TEST_CASE("")
{

}

//CACTI



//GAME
