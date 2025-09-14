/**
 * @file player.h
 * @brief Player character data structure and properties
 */

#pragma once

#include "raylib.h"

/**
 * @brief Player character data structure
 */
typedef struct Player
{
    Vector2 position; ///< Current position in world coordinates
    float speed;      ///< Current movement speed (may be modified)
    float size;       ///< Size of the player collision box
} Player;
