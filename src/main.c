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

typedef struct Circle {
  Vector2 center;
  float radius;
} Circle;

typedef struct Player {
  Vector2 position;
  float baseSpeed;
  float speed;
  float size;
} Player;

typedef struct Map {
  Rectangle bounds;
  Color color;
  float borderThickness;
} Map;

typedef struct Obstacle {
  Rectangle bounds;
  Color color;
} Obstacle;

static int screenWidth = 1200;
static int screenHeight = 900;

static Player player = {0};
static Camera2D camera = {0};
static Map map = {0};
static Obstacle obstacle = {0};

static void InitGame(void);
static void UpdateGame(void);
static void DrawGame(void);
float ClampFloat(float value, float min, float max);

int main(void) {

  InitWindow(screenWidth, screenHeight, "Game!");

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

void InitGame(void) {
  player.position = (Vector2){(float)screenWidth / 2, (float)screenHeight / 2};
  player.baseSpeed = 2.0f;
  player.speed = player.baseSpeed;
  player.size = 30;

  camera.target = player.position;
  camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  map.bounds.width = 750;
  map.bounds.height = 750;
  map.bounds.x = (screenWidth - map.bounds.width) / 2;
  map.bounds.y = (screenHeight - map.bounds.height) / 2;
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

  // Create player collision circle for this frame
  Circle playerCircle = {.center = newPosition, .radius = player.size / 2};

  // Check collision with obstacle
  if (!CheckCollisionCircleRec(newPosition, player.size / 2, obstacle.bounds)) {
    // Only update position if there's no collision
    player.position.x =
        ClampFloat(newPosition.x, map.bounds.x + map.borderThickness + player.size / 2,
                   map.bounds.x + map.bounds.width - map.borderThickness - player.size / 2);

    player.position.y =
        ClampFloat(newPosition.y, map.bounds.y + map.borderThickness + player.size / 2,
                   map.bounds.y + map.bounds.height - map.borderThickness - player.size / 2);
  }

  // Camera
  camera.target = player.position;
}

/**
 * Draws a single frame
 */
void DrawGame(void) {

  BeginDrawing();
  ClearBackground(RAYWHITE);
  BeginMode2D(camera);

  // Draw main map area
  DrawRectangleRec(map.bounds, map.color);

  // Draw border
  DrawRectangleLinesEx(map.bounds, map.borderThickness, BLACK);

  // Draw obstacle
  DrawRectangleRec(obstacle.bounds, obstacle.color);

  // Draw player
  DrawCircleV(player.position, player.size / 2, RED);

  EndMode2D();
  EndDrawing();
}

/**
 * Clamps a float between a min and max range
 * @return float Original value if within range, or min/max otherwise
 */
float ClampFloat(float value, float min, float max) {
  const float res = value < min ? min : value;
  return res > max ? max : res;
}
