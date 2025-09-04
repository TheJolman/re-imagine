/**
 * @file battle.c
 * @brief Battle system implementation
 */

#include "battle.h"
#include "map.h"
#include "menu.h"
#include "mon.h"
#include "raylib.h"
#include <assert.h>
#include <stdint.h>

// Should these be moved into initBattleUI ?
constexpr uint32_t WINDOW_MARGIN = 50;
constexpr uint32_t TEXT_HEIGHT = 150;
constexpr Color TINT = WHITE;
constexpr float ROTATION = 0.0;
constexpr float SCALE = 0.6f;

typedef struct
{
    Rectangle text_box;
    Vector2 player_mon_pos;
    Vector2 enemy_mon_pos;
    Vector2 action_menu_pos;
    Vector2 status_bar_pos;
} BattleUI;

typedef enum
{
    BATTLE_MENU,
    BATTLE_ATTACK,
    BATTLE_ITEMS,
    BATTLE_RUN,
    BATTLE_SWITCH,
} BattleState;

static BattleState battle_state = BATTLE_MENU;

// clang-format off
static void attack_select() { battle_state = BATTLE_ATTACK; }
static void items_select()  { battle_state = BATTLE_ITEMS; }
static void run_select()    { battle_state = BATTLE_RUN; }
static void switch_select() { battle_state = BATTLE_SWITCH; }
// clang-format on

Mon *player_mon = nullptr;
Mon *enemy_mon = nullptr;
BattleUI ui = {0};
static bool battle_initialized = false;
static Menu *action_menu = nullptr;

static void action_menu_create()
{
    const char *item_texts[] = {"ATTACK", "ITEMS", "RUN", "SWITCH"};
    void (*select_callbacks[])(void) = {attack_select, items_select, run_select, switch_select};
    MenuConfig config = {
        .title = "BATTLE MENU",
        .rect = {ui.text_box.x + ui.text_box.width * 0.5f + 10, ui.text_box.y + 30, 0, 0},
        .font_size = 20,
        .layout = MENU_LAYOUT_GRID,
        .num_rows = 2,
        .num_cols = 2,
    };

    Result res = menu_create(&config, item_texts, select_callbacks, 4);
    if (res.err)
    {
        error_log(res.err);
        return;
    }
    action_menu = (Menu *)res.value;
}

static void action_menu_end()
{
    if (action_menu)
        menu_destroy(action_menu);

    action_menu = nullptr;
}

static void action_menu_display()
{
    if (!action_menu)
    {
        action_menu_create();
    }

    DrawLine(ui.text_box.x + ui.text_box.width * 0.5f, ui.text_box.y,
             ui.text_box.x + ui.text_box.width * 0.5f, ui.text_box.y + ui.text_box.height, GRAY);

    menu_draw(action_menu);
    menu_handle_input(action_menu);
}

static void init_battle_ui(void)
{
    ui.text_box = (Rectangle){WINDOW_MARGIN, screen.height - (WINDOW_MARGIN + TEXT_HEIGHT),
                              screen.width - WINDOW_MARGIN * 2, TEXT_HEIGHT};

    // TODO: Get consistent asset sizes
    ui.player_mon_pos = (Vector2){screen.width * 0.6f, screen.height * 0.35f};
    ui.enemy_mon_pos = (Vector2){screen.width * 0.05f, screen.height * 0.1f};
    ui.action_menu_pos = (Vector2){ui.text_box.x + 20, ui.text_box.y + 20};
    ui.status_bar_pos = (Vector2){ui.text_box.x + 20, ui.text_box.y + 80};

    battle_state = BATTLE_MENU;

    if (!player_mon)
    {
        Result res = create_mon("froge");
        if (res.err)
        {
            error_exit(1, "%s", res.err);
        }
        else
        {
            player_mon = (Mon *)res.value;
        }
        player_mon->hp = 100;
        load_mon_texture(player_mon, BACK);
    }

    if (!enemy_mon)
    {
        Result res = create_mon("froge");
        if (res.err)
        {
            error_exit(1, "%s", res.err);
        }
        else
        {
            enemy_mon = (Mon *)res.value;
        }
        enemy_mon->hp = 80;
        load_mon_texture(enemy_mon, FRONT);
    }
}

static void render_mon(Mon *mon, Vector2 position)
{
    if (!mon)
        return;

    if (!mon->texture)
        return;

    if (!IsTextureValid(*mon->texture))
        return;

    DrawTextureEx(*mon->texture, position, ROTATION, SCALE, TINT);
}

static void render_text_box(void)
{
    DrawRectangleLines(ui.text_box.x, ui.text_box.y, ui.text_box.width, ui.text_box.height, WHITE);
}

static void render_action_menu(void)
{
    switch (battle_state)
    {
    case BATTLE_MENU:
        action_menu_display();
        break;
    case BATTLE_ATTACK:
        // attack_menuDisplay();
        break;
    case BATTLE_ITEMS:
        // items_menuDisplay();
        break;
    case BATTLE_RUN:
        // runMenuDisplay();
        break;
    case BATTLE_SWITCH:
        // switch_menuDisplay();
        break;
    }
}

static void render_battle_ui(void)
{
    render_text_box();
    render_action_menu();

    if (player_mon)
        render_mon(player_mon, ui.player_mon_pos);

    if (enemy_mon)
        render_mon(enemy_mon, ui.enemy_mon_pos);
}

void battle_scene_render(void)
{
    if (!battle_initialized)
    {
        init_battle_ui();
        battle_initialized = true;
    }

    DrawText("Battle scene is active!\nPress B to go back!", 50, 50, 20, DARKGRAY);
    render_battle_ui();
}

void battle_scene_end(void)
{
    if (player_mon)
    {
        destroy_mon(player_mon);
        player_mon = nullptr;
    }

    if (enemy_mon)
    {
        destroy_mon(enemy_mon);
        enemy_mon = nullptr;
    }

    action_menu_end();
    battle_state = BATTLE_MENU;
    battle_initialized = false;
}