#ifndef GAME_H
#define GAME_H

#include "player.h"

typedef enum
{
    FREE_ROAM,
    BATTLE_SCENE,
    PAUSED,
    TITLE_SCREEN,
} GameState;

extern Player player;
extern Camera2D camera;
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
