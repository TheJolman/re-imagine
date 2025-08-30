#pragma once

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
void init_game(void);

/**
 * Updates game variables before next frame is drawn
 */
void update_game(void);

/**
 * Draws a single frame
 */
void draw_game(void);
