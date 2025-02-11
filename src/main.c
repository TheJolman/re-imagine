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
#include "raymath.h"

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Game!");

  Vector2 playerPosition = {(float)screenWidth / 2, (float)screenHeight / 2};
  float baseMoveSpeed = 2.0f;
  Camera2D camera = {0};
  camera.target = playerPosition;
  camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  SetTargetFPS(60);

  // Main game loop
  while (!WindowShouldClose()) {
    // Update
    // -------------------------------------------------------------------------
    // Movement
    float moveSpeedModifier = 1.0f;
    if (IsKeyDown(KEY_LEFT_SHIFT)) {
      moveSpeedModifier = 2.0f;
    }

    float moveSpeed = baseMoveSpeed * moveSpeedModifier;
    Vector2 moveDirection = {0.0f, 0.0f};

    if (IsKeyDown(KEY_W)) {
      moveDirection.y -= 1.0f;
    }
    if (IsKeyDown(KEY_S)) {
      moveDirection.y += 1.0f;
    }
    if (IsKeyDown(KEY_A)) {
      moveDirection.x -= 1.0f;
    }
    if (IsKeyDown(KEY_D)) {
      moveDirection.x += 1.0f;
    }

    if (moveDirection.x != 0.0f || moveDirection.y != 0.0f) {
      moveDirection = Vector2Normalize(moveDirection);
      playerPosition.x += moveDirection.x * moveSpeed;
      playerPosition.y += moveDirection.y * moveSpeed;
    }

    // Camera
    camera.target = playerPosition;
    // -------------------------------------------------------------------------

    // Draw
    // -------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);

    BeginMode2D(camera);
    DrawCircleV(playerPosition, 20, RED);
    DrawRectangle(300, 150, 50, 50, GRAY);
    EndMode2D();

    EndDrawing();
    // -------------------------------------------------------------------------
  }

  CloseWindow();

  return 0;
}
