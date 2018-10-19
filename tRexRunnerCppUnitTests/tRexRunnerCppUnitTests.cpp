// tRexRunnerCppUnitTests.cpp : Defines the entry point for the console application.
//

#define CATCH_CONFIG_MAIN
#include "stdafx.h"
#include "catch.hpp"
#include "Game.h"

sf::RenderWindow testWindow(sf::VideoMode(WIDTH, HEIGHT), "tRexRunner");
class TestGame : public Game { using Game::Game; };

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
  CHECK(testTRex.m_state == TRex::JUMPING);
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
  REQUIRE(testTRex.m_state == TRex::RUNNING1);
}

TEST_CASE("TRex Update method should not switch state if jumping")
{
  TRex testTRex(5.0, 5.0);
  testTRex.Jump();
  TRex::TRexStates initialState = testTRex.m_state;
  testTRex.Update();
  REQUIRE(testTRex.m_state == initialState);
}

TEST_CASE("TRex Run method should not switch state if jumping")
{
  TRex testTRex(5.0, 5.0);
  testTRex.Jump();
  TRex::TRexStates initialState = testTRex.m_state;
  testTRex.Run();
  REQUIRE(testTRex.m_state == initialState);
}

TEST_CASE("TRex Run method should switch state to RUNNING1 if TRex is not jumping ")
{
  TRex testTRex(5.0, 5.0);
  TRex::TRexStates initialState = testTRex.m_state;
  testTRex.Run();
  CHECK(testTRex.m_state == TRex::RUNNING1);
  testTRex.Duck();
  testTRex.Run();
  CHECK(testTRex.m_state == TRex::RUNNING1);
  testTRex.Jump();
  testTRex.Run();
  CHECK_FALSE(testTRex.m_state == TRex::RUNNING1);
}

TEST_CASE("TRex Run method should not switch state if running")
{
  TRex testTRex(5.0, 5.0);
  testTRex.Update();
  TRex::TRexStates initialState = testTRex.m_state;
  testTRex.Run();
  REQUIRE(testTRex.m_state == initialState);
}

TEST_CASE("TRex should change from RUNNING1 to RUNNING2 after LIMB_CHANGE_COUNTER frames")
{
  TRex testTRex(5.0, 5.0);
  for (int i = 0; i < LIMB_CHANGE_COUNTER; i++)
  {
    testTRex.Update();
  }
  REQUIRE(testTRex.m_state == TRex::RUNNING2);
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

TEST_CASE("Cactus should create all types of cacti")
{
  for (int i = 1; i < 4; i++)
  {
    Cactus* testCactus = new Cactus(rand(), i);
    REQUIRE(testCactus != NULL);
    delete(testCactus);
  }
}

//HORIZON BUMPS

Horizon testHorizon1(1);
Horizon testHorizon2(2);

TEST_CASE("Creating 2 horizon bumps makes the one with 1 in the constructor 2 times closer than the one with 2 in the constructor")
{
  REQUIRE(testHorizon1.GetPositionX() == testHorizon2.GetPositionX() / 2);
}

TEST_CASE("Move method should move horizon bumps by \"currentGameSpeed\" frames")
{
  float previousPosition = testHorizon1.GetPositionX();
  testHorizon1.Move(GAME_INITIAL_SPEED);
  REQUIRE(previousPosition == testHorizon1.GetPositionX() + GAME_INITIAL_SPEED);
}

//GAME
TEST_CASE("InitGame() should set score to 0")
{
  TestGame testGame(&testWindow);
  testGame.InitGame();
  REQUIRE(testGame.GetScore() == 0);
  testGame.GameOver(&testGame);
}

TEST_CASE("HighScore should be same as score when score exceeds HighScore")
{
  TestGame testGame(&testWindow);
  Sleep(100);
  testGame.SetScore(testGame.GetHighScore() + 1);
  testGame.HandlePeriodicIncrements(clock());
  REQUIRE(testGame.GetHighScore() == testGame.GetScore());
}

TEST_CASE("Score should not change if time passed is less than GAME_SCORE_INCREMENT")
{
  TestGame testGame(&testWindow);
  Sleep(GAME_SCORE_INCREMENT - 5);
  testGame.HandlePeriodicIncrements(clock());
  REQUIRE(testGame.GetScore() == 0);
}

TEST_CASE("Score should increase by 1 every time time passed is GAME_SCORE_INCREMENT or more")
{
  TestGame testGame(&testWindow);
  int testScore = 0;
  while (testScore < 10)
  {
    testScore = testGame.GetScore() + 1;
    Sleep(GAME_SCORE_INCREMENT);
    testGame.HandlePeriodicIncrements(clock());
    CHECK(testGame.GetScore() == testScore);
  }
}

TEST_CASE("DeleteObstacles should clear all obstacles from Obstacke vector")
{
  TestGame testGame(&testWindow);
  Pterodactyl* testPterodactyl = new Pterodactyl(10);
  Cactus* testCactus1 = new Cactus(0, 1);
  Cactus* testCactus2 = new Cactus(10, 2);
  Cactus* testCactus3 = new Cactus(20, 3);
  Cactus* testCactus4 = new Cactus(30, 4);
  std::vector<Obstacle*> testObstacles = { testPterodactyl, testCactus1, testCactus2, testCactus3, testCactus4 };
  testGame.DeleteObstacles(&testObstacles);
  REQUIRE(testObstacles.empty());
}

TEST_CASE("ClearObstaclesThatPassed should clear first obstacle if its positionX is less than 0")
{
  TestGame testGame(&testWindow);
  Pterodactyl* testPterodactyl = new Pterodactyl(-10);
  Cactus* testCactus1 = new Cactus(1, 1);
  Cactus* testCactus2 = new Cactus(10, 2);
  Cactus* testCactus3 = new Cactus(20, 3);
  Cactus* testCactus4 = new Cactus(30, 4);
  std::vector<Obstacle*> testObstacles = { testPterodactyl, testCactus1, testCactus2, testCactus3, testCactus4 };
  testGame.ClearObstaclesThatPassed(&testObstacles);
  CHECK(testObstacles.size() == 4);
}

TEST_CASE("UpdateAllObstacles should add obstacles untill there are MAX_OBSTACLE_COUNT")
{
  TestGame testGame(&testWindow);
  std::vector<Obstacle*> testObstacles;
  testGame.UpdateAllObstacles(&testObstacles);
  REQUIRE(testObstacles.size() == MAX_OBSTACLE_COUNT);
}

TEST_CASE("MoveBumps should move horizon bumps by currentGameSpeed to the left")
{
  TestGame testGame(&testWindow);
  Horizon* testHorizonBump1 = new Horizon(1);
  Horizon* testHorizonBump2 = new Horizon(2);
  float bump1FirstPosX = testHorizonBump1->GetPositionX();
  float bump2FirstPosX = testHorizonBump2->GetPositionX();
  testGame.MoveBumps(testHorizonBump1, testHorizonBump2, GAME_INITIAL_SPEED);
  CHECK(bump1FirstPosX == testHorizonBump1->GetPositionX() + GAME_INITIAL_SPEED);
  CHECK(bump1FirstPosX == testHorizonBump1->GetPositionX() + GAME_INITIAL_SPEED);
}

TEST_CASE("HandleButtonPress should make tRex jump if up key is pressed")
{
  TestGame testGame(&testWindow);
  TRex testTRex(5.0, 5.0);
  testGame.HandleButtonPress(true, false, false, &testTRex);
  REQUIRE(testTRex.m_state == TRex::JUMPING);
}
TEST_CASE("HandleButtonPress should make tRex duck if down key is pressed")
{
  TestGame testGame(&testWindow);
  TRex testTRex(5.0, 5.0);
  testGame.HandleButtonPress(false, true, false, &testTRex);
  REQUIRE(testTRex.m_state == TRex::DUCKING1);
}

TEST_CASE("IsButtonPressed should return false (no buttons pressed during test")
{
  TestGame testGame(&testWindow);
  REQUIRE(testGame.IsButtonPressed(rand()) == false);
}