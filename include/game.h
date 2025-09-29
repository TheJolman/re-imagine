/**
 * @file game.h
 * @brief Core game state management and main game loop functions
 */

#pragma once

#include "map.h"
#include "player.h"

/**
 * @brief Configuration options for game.c
 */
typedef struct
{
    Vector2 player_initial_pos;
    float player_base_speed;
    float player_sprint_modifier;
    uint32_t player_size;
    float camera_base_zoom;
} GameConfig;

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

/**
 * @brief Holds pointers to game-related objects as well as the game state.
 */
typedef struct
{
    Player player;
    Camera2D camera;
    GameState state;
    Map *map;
} GameContext;

extern GameContext ctx;
constexpr GameConfig cfg = {
    .player_base_speed = 5.0f,
    .player_sprint_modifier = 2.0f,
    .player_initial_pos = (Vector2){100, 100},
    .player_size = 30,
    .camera_base_zoom = 1.0f,
};
/**
 * @brief Loads initial values on game startup
 *
 * Initializes the player, camera, and other game systems
 */
void game_init(void);

/**
 * @brief Updates game variables before next frame is drawn
 *
 * Handles input, updates player position, and manages state transitions
 */
void game_update(void);

/**
 * @brief Draws a single frame
 */
void game_draw(void);

/**
 * @brief allows other modules to set the game state
 */
void game_set_state(GameState state);

/**
 * @brief Frees resources held in game.c
 */
void game_cleanup(void);
