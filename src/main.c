/*******************************************************************************************
 *
 *   VGDC Game Project
 *
 *   <Game title>
 *   <Game description>
 *
 *   This game has been created using raylib (www.raylib.com)
 *
 *   Copyright (c) 2025 Joshua Holman
 *
 ********************************************************************************************/

#include "raylib.h"

#include "game.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

int main(void) {

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game!");
  SetTargetFPS(60);
  InitGame();

  // Main game loop
  while (true) {
    UpdateGame();
    DrawGame();
  }

  UnloadMap(tileMap);
  CloseWindow();

  return 0;
}
