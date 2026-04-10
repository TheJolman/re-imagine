#pragma once

#include <raylib.h>

#include "components.h"

/**
 * @brief Player character data structure
 */
typedef struct {
    Vector2 position;       ///< Current position in world coordinates
    Vector2 velocity;       ///< Velocity vector
    float speed;
    float sprint_modifier;   ///< Amount to increase speed by when sprinting
    float size;              ///< Size of the player collision box
    Rectangle collision_box; ///< Calculated collision box
    Sprite sprite;
    Texture2D sprite_sheet; ///< Sprite sheet texture for animations
    PlayerAnimations anims;
} Player;

/** Used for creating players or npcs
 */
typedef struct {
    Vector2 init_position;
    float base_speed;
    float sprint_modifier;
    uint32_t size;
} PlayerConfig;

void player_init(Player *player, const PlayerConfig *cfg);
void player_draw(const Player *player);
void player_update(Player *player, Camera2D *camera);
void player_cleanup(Player *player);
