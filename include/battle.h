/**
 * @file battle.h
 * @brief Battle system management and rendering
 */

#pragma once

#include "raylib.h"

typedef struct
{
    Rectangle text_box;
    Vector2 player_mon_pos;
    Vector2 enemy_mon_pos;
    Vector2 action_menu_pos;
    Vector2 status_bar_pos;
} BattleUI;

/**
 * @brief Renders the battle scene interface
 *
 * Draws the battle UI, monsters, and handles battle-specific rendering
 */
void battle_scene_render(void);

/**
 * @brief Cleans up battle scene resources
 *
 * Called when exiting the battle scene to free allocated memory
 */
void battle_scene_end(void);
