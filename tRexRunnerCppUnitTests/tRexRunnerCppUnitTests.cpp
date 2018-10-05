// tRexRunnerCppUnitTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Game.h"

sf::RenderWindow testWindow(sf::VideoMode(WIDTH, HEIGHT), "tRexRunner");

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

TEST_CASE("Pterodactyl should have the same distance as position X when created")
{
  Pterodactyl testPterodactyl(10);
  REQUIRE(testPterodactyl.GetPositionX() == 10);
}

TEST_CASE("Pterodactyl update method should move it by \"currentGameSpeed\" frames")
{
  Pterodactyl testPterodactyl(10);
  testPterodactyl.Update(GAME_INITIAL_SPEED);
  REQUIRE(testPterodactyl.GetPositionX() == 10 - GAME_INITIAL_SPEED);
}

//CACTI

TEST_CASE("Cactus should have the same distance as position X when created")
{
  Cactus testCactus(5, rand() % 4);
  REQUIRE(testCactus.GetPositionX() == 5);
}

TEST_CASE("Cactus update method should move it by \"currentGameSpeed\" frames")
{
  Cactus testCactus(10, rand());
  testCactus.Update(GAME_INITIAL_SPEED);
  REQUIRE(testCactus.GetPositionX() == 10 - GAME_INITIAL_SPEED);
}

//HORIZON BUMPS

Horizon testHorizon1(1);
Horizon testHorizon2(2);

TEST_CASE("Creating 2 horizon bumps makes the one with 1 in the constructor 2 times closer than the one with 2 in the constructor")
{
  REQUIRE(testHorizon1.GetPositionX() == testHorizon2.GetPositionX() / 2);
}

TEST_CASE("Move method should move horizon bumps by gameSpeed")
{
  float previousPosition = testHorizon1.GetPositionX();
  testHorizon1.Move(GAME_INITIAL_SPEED);
  REQUIRE(previousPosition == testHorizon1.GetPositionX() + GAME_INITIAL_SPEED);
}

//GAME

Game testGame(&testWindow);

TEST_CASE("TEST DUH")
{
  testGame.InitGame();
  REQUIRE(1 == 0);
}
