/**
 * @file battle.h
 * @brief Battle system management and rendering
 */

#pragma once

#include "menu.h"
#include "mon.h"
#include "raylib.h"
#include <stdint.h>

/**
 * @brief Read-only configuration options for the battle interface
 */
typedef struct
{
    uint32_t window_margin;
    uint32_t text_height;
    Color mon_tint;
    float mon_rotation;
    float mon_scale;

    // Y position as a fixed offset from the screen edge
    float player_mon_y_margin;
    float enemy_mon_y_margin;

    // X position as a fixed offset from the screen edge
    float player_mon_x_margin;
    float enemy_mon_x_margin;

    // Offsets for UI elements within the text box
    Vector2 action_menu_pos_offset;
    Vector2 status_bar_pos_offset;

    // Config for the action menu itself
    float action_menu_split_x_percent;
    Vector2 action_menu_rect_offset;
    uint32_t action_menu_font_size;
} BattleUIConfig;

/**
 * @brief Calculated configuration options for the battle interface
 */
typedef struct
{
    Rectangle text_box;
    Vector2 action_menu_pos;
    Vector2 status_bar_pos;
} BattleUILayout;

/**
 * @brief Holds pointers to battle-related objects as well as the battle state.
 */
typedef struct
{
    Mon *player_mon;
    Mon *enemy_mon;
    BattleUILayout *battle_ui;
    bool initialized;
    Menu *action_menu;
    enum
    {
        BATTLE_MENU,
        BATTLE_ATTACK,
        BATTLE_ITEMS,
        BATTLE_RUN,
        BATTLE_SWITCH,
    } state;
} BattleContext;

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
