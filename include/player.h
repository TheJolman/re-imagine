/**
 * @file player.h
 * @brief Player character data structure and properties
 */

#pragma once

#include "components.h"
#include <raylib.h>

/**
 * @brief Player character data structure
 */
typedef struct
{
    Position position;       ///< Current position in world coordinates
    Velocity velocity;       ///< Velocity vector
    float sprint_modifier;   ///< Amount to increase speed by when sprinting
    float size;              ///< Size of the player collision box
    Rectangle collision_box; ///< Calculated collision box
    Sprite sprite;
    Texture2D sprite_sheet; ///< Sprite sheet texture for animations
} Player;

void update_player_draw_frame(Vector2 positionw);
void create_player_sprite_animation(void);
void _player_move(void);
void _player_draw(void);
void draw_debug_info(void);