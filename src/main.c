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

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawText("Hi mom", 190, 200, 20,
             LIGHTGRAY);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
