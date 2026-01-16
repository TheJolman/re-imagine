#pragma once

#include "map.h"
#include "player.h"

/**
 * @brief Game state enumeration
 *
 * Represents the current state of the game for the state machine
 */
typedef enum {
    FREE_ROAM,    ///< Player can move freely in the overworld
    BATTLE_SCENE, ///< Player is in a battle encounter
    PAUSED,       ///< Game is paused
    TITLE_SCREEN, ///< Showing the title screen
} GameState;

/**
 * @brief Holds pointers to game-related objects as well as the game state.
 */
typedef struct {
    Player player;
    Camera2D camera;
    GameState state;
    Map *map;
} GameContext;

/**
 * Sets up window and runs main game loop
 */
int game_run();
