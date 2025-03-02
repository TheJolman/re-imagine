#include "game.h"

#include "raylib.h"
#include "raymath.h"
#include "utils.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

Player player = {0};
Camera2D camera = {0};
Map tileMap = {0};
MapData mapData = {0};
Obstacle obstacle = {0};
GameState state = {0};

void InitGame(void) {
  state = FREE_ROAM;
  tileMap = LoadTiled("resources-test/desert.json");
  player.position = (Vector2){(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2};
  player.baseSpeed = 5.0f;
  player.speed = player.baseSpeed;
  player.size = 30;

  camera.target = player.position;
  camera.offset = (Vector2){SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
  camera.zoom = 1.0f;

  mapData.bounds.width = 1280; // these were obtained via guessing
  mapData.bounds.height = 1280;
  mapData.bounds.x = 0;
  mapData.bounds.y = 0;
}

void UpdateGame(void) {
  if (IsKeyPressed(KEY_B)) {
    if (state == FREE_ROAM) {
      state = BATTLE_SCENE;
    } else if (state == BATTLE_SCENE) {
      state = FREE_ROAM;
    }
  }

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

  // Only update position if there's no collision
  player.position.x = ClampFloat(newPosition.x, mapData.bounds.x + +player.size / 2,
                                 mapData.bounds.x + mapData.bounds.width - player.size / 2);

  player.position.y = ClampFloat(newPosition.y, mapData.bounds.y + player.size / 2,
                                 mapData.bounds.y + mapData.bounds.height - player.size / 2);

  // Camera
  camera.target = player.position;
}

void DrawGame(void) {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  switch (state) {
  case FREE_ROAM:
    BeginMode2D(camera);
    DrawTiled(tileMap, 0, 0, WHITE);

    // Draw player
    DrawCircleV(player.position, player.size / 2, RED);

    EndMode2D();
    DrawText("Press B to enter the Battle Scene!", 50, 50, 20, DARKGRAY);
    break;
  case BATTLE_SCENE:
    DrawText("Battle scene is active!\nPress B to go back!", 50, 50, 20, DARKGRAY);
    break;
  case PAUSE:
    break;
  case TITLE:
    break;
  }

  EndDrawing();
}
