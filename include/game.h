/**
 * @file game.h
 * @brief Core game state management and main game loop functions
 */

#pragma once

#include "map.h"
#include "player.h"

/**
 * @brief Game state enumeration
 *
 * Represents the current state of the game for the state machine
 */
typedef enum
{
    FREE_ROAM,    ///< Player can move freely in the overworld
    BATTLE_SCENE, ///< Player is in a battle encounter
    PAUSED,       ///< Game is paused
    TITLE_SCREEN, ///< Showing the title screen
} GameState;

extern Player player;   ///< Global player instance
extern Camera2D camera; ///< Global 2D camera for rendering
extern GameState state; ///< Current game state

/**
 * @brief Loads initial values on game startup
 *
 * Initializes the player, camera, and other game systems
 */
void init_game(void);

/**
 * @brief Updates game variables before next frame is drawn
 *
 * Handles input, updates player position, and manages state transitions
 */
void update_game(void);

/**
 * @brief Draws a single frame
 *
 * @param map The map to render in the current frame
 */
void draw_game(Map *map);
