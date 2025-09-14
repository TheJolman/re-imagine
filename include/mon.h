/**
 * @file mon.h
 * @brief Monster/Pokemon system definitions and functions
 */

#pragma once

#include "components.h"
#include "raylib.h"
#include "utils.h"

/**
 * @brief Texture type for monster sprites
 */
typedef enum
{
    FRONT, ///< Front-facing sprite (opponent's view)
    BACK   ///< Back-facing sprite (player's view)
} MonSpriteView;

/**
 * @brief A move/attack that a monster can perform
 */
typedef struct
{
    const char *name;      ///< Name of the move
    const unsigned damage; ///< Damage dealt by this move
} Move;

/**
 * @brief Monster/Pokemon data structure
 */
typedef struct
{
    const char *name;          ///< Monster's name
    Sprite sprite;             ///< Monster's sprite
    MonSpriteView sprite_view; ///< Determines if we get the front or back view
    Move moves[4];             ///< Array of up to 4 moves
    unsigned hp;               ///< Current hit points
} Mon;

/**
 * @brief Creates a new monster with the given name
 *
 * @param name The name of the monster to create
 * @return Result containing the created monster or error information
 */
Result create_mon(char *name);

/**
 * @brief Destroys a monster and frees its resources
 *
 * @param mon Pointer to the monster to destroy
 */
void destroy_mon(Mon *mon);

/**
 * @brief Loads the appropriate texture for a monster
 *
 * @param mon Pointer to the monster
 * @param textureType Type of texture to load (FRONT or BACK)
 */
void load_mon_texture(Mon *mon, MonSpriteView textureType);
