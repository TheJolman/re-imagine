/**
 * @file battle.h
 * @brief Battle system management and rendering
 */

#pragma once

#include "menu.h"
#include "mon.h"
#include "raylib.h"
#include <stdint.h>

typedef struct
{
    Rectangle text_box;
    Vector2 player_mon_pos;
    Vector2 enemy_mon_pos;
    Vector2 action_menu_pos;
    Vector2 status_bar_pos;
} BattleUI;

/**
 * @brief Configuration options for the battle UI
 */
typedef struct
{
    uint32_t window_margin;
    uint32_t text_height;
    Color mon_tint;
    float mon_rotation;
    float mon_scale;
} BattleUIConfig;

/**
 * @brief Holds pointers to battle-related objects as well as the battle state.
 */
typedef struct
{
    Mon *player_mon;
    Mon *enemy_mon;
    BattleUI *battle_ui;
    bool initialized;
    Menu *action_menu;
    enum {
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
