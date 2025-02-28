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
#include "stdlib.h"

#define RAYLIB_TILESON_IMPLEMENTATION
#include "raylib-tileson.h"

#include "map.h"
#include "player.h"
#include "utils.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

static Player player = {0};
static Camera2D camera = {0};
static Map tileMap = {0};
static MyMap map = {0};
static Obstacle obstacle = {0};
static bool battleSceneActive = false;

static void InitGame(void);
static void UpdateGame(void);
static void DrawGame(void);

int main(void) {

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game!");

  SetTargetFPS(60);
  InitGame();

  // Main game loop
  while (!WindowShouldClose()) {
    UpdateGame();
    DrawGame();
  }

  CloseWindow();

  return 0;
}

/**
 * Loads initial values on game startup
 */
void InitGame(void) {
  tileMap = LoadTiled("resources-test/desert.json");
  player.position = (Vector2){(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2};
  player.baseSpeed = 2.0f;
  player.speed = player.baseSpeed;
  player.size = 30;

  camera.target = player.position;
  camera.offset = (Vector2){SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  map.bounds.width = 750;
  map.bounds.height = 750;
  map.bounds.x = (SCREEN_WIDTH - map.bounds.width) / 2;
  map.bounds.y = (SCREEN_HEIGHT - map.bounds.height) / 2;
  map.color = GRAY;
  map.borderThickness = 10.0f;

  // Create an obstacle in the middle-right of the map
  obstacle.bounds = (Rectangle){
      map.bounds.x + map.bounds.width * 0.7f,  // x position
      map.bounds.y + map.bounds.height * 0.5f, // y position
      60,                                      // width
      60                                       // height
  };
  obstacle.color = DARKGRAY;
}

/**
 * Updates game variables before next frame is drawn
 */
void UpdateGame(void) {
  if (IsKeyPressed(KEY_B))
    battleSceneActive = !battleSceneActive;

  // Movement
  float moveSpeedModifier = 1.0f;
  if (IsKeyDown(KEY_LEFT_SHIFT)) {
    moveSpeedModifier = 2.0f;
  }

  player.speed = player.baseSpeed * moveSpeedModifier;
  Vector2 moveDirection = {0.0f, 0.0f};

  if (IsKeyDown(KEY_W))
    moveDirection.y -= 1.0f;
  if (IsKeyDown(KEY_S))
    moveDirection.y += 1.0f;
  if (IsKeyDown(KEY_A))
    moveDirection.x -= 1.0f;
  if (IsKeyDown(KEY_D))
    moveDirection.x += 1.0f;

  if (moveDirection.x != 0.0f || moveDirection.y != 0.0f) {
    moveDirection = Vector2Normalize(moveDirection);
  }

  // Calculate new position
  Vector2 newPosition = {player.position.x + moveDirection.x * player.speed,
                         player.position.y + moveDirection.y * player.speed};

  // Camera
  camera.target = player.position;
}

/**
 * Draws a single frame
 */
void DrawGame(void) {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  if (battleSceneActive) {
    DrawText("Battle scene is active!\nPress B to go back!", 50, 50, 20, DARKGRAY);
  } else {
    BeginMode2D(camera);
    DrawTiled(tileMap, 0, 0, WHITE);
    // system("pwd");

    // Draw main map area
    // DrawRectangleRec(map.bounds, map.color);

    // Draw border
    // DrawRectangleLinesEx(map.bounds, map.borderThickness, BLACK);

    // Draw obstacle
    // DrawRectangleRec(obstacle.bounds, obstacle.color);

    // Draw player
    DrawCircleV(player.position, player.size / 2, RED);

    EndMode2D();
    DrawText("Press B to enter the Battle Scene!", 50, 50, 20, DARKGRAY);
  }
  EndDrawing();
}
