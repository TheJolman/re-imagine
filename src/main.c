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
#include "stdbool.h"

#include "game.h"
#include "map.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

Screen screen = {0};

int main(void) {

  screen.width = SCREEN_WIDTH;
  screen.height = SCREEN_HEIGHT;

  InitWindow(screen.width, screen.height, "Game!");
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
