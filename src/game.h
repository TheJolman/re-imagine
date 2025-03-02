#ifndef GAME_H
#define GAME_H

#include "map.h"
#include "player.h"

#define RAYLIB_TILESON_IMPLEMENTATION
#include "raylib-tileson.h"

typedef enum {
  FREE_ROAM,
  BATTLE_SCENE,
  PAUSED,
  TITLE_SCREEN,
} GameState;

extern Player player;
extern Camera2D camera;
extern Map tileMap;
extern MapData mapData;
extern Obstacle obstacle;
extern GameState state;

/**
 * Loads initial values on game startup
 */
void InitGame(void);

/**
 * Updates game variables before next frame is drawn
 */
void UpdateGame(void);

/**
 * Draws a single frame
 */
void DrawGame(void);

#endif // !GAME_H
