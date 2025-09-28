/**
 * @file player.h
 * @brief Player character data structure and properties
 */

#pragma once

#include <raylib.h>
#include "components.h"



/**
 * @brief Player character data structure
 */
typedef struct
{
    Position position;     ///< Current position in world coordinates
    Velocity velocity;     ///< Velocity vector
    float sprint_modifier; ///< Amount to increase speed by when sprinting
    float size;            ///< Size of the player collision box
    Sprite sprite;
} Player;

void UpdatePlayerDrawFrame(void);
void CreatePlayerSpriteAnimation(void);
void _player_move(void);
void _player_draw(void);