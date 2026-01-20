#pragma once

#include <raylib.h>

#include "components.h"

/**
 * @brief Player character data structure
 */
typedef struct {
    Position position;       ///< Current position in world coordinates
    Velocity velocity;       ///< Velocity vector
    float sprint_modifier;   ///< Amount to increase speed by when sprinting
    float size;              ///< Size of the player collision box
    Rectangle collision_box; ///< Calculated collision box
    Sprite sprite;
    Texture2D sprite_sheet;  ///< Sprite sheet texture for animations
    PlayerAnimations anims;
} Player;

typedef struct {
    Position init_position;
    float base_speed;
    float sprint_modifier;
    uint32_t size;
} PlayerConfig;

void player_draw();
void player_move();
