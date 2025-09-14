/**
 * @file battle.c
 * @brief Battle system implementation
 * Note that 'action_menu' refers to the top-level menu that includes 'attack', 'items', 'run', and
 * 'switch' options.
 */

#include "battle.h"
#include "map.h"
#include "raylib.h"

static constexpr BattleUIConfig ui_config = {
    .window_margin = 50,
    .text_height = 150,
    .mon_tint = WHITE,
    .mon_rotation = 0.0,
    .mon_scale = 0.6f,
};

static BattleContext battle_ctx = {0};

/**
 * Calculates location of UI elements, loads monster assets into memory, and sets
 * the initial state of the battle.
 */
static void _init_battle_ui(void)
{
    battle_ctx.battle_ui = heap_list.malloc(sizeof(BattleUILayout));
    if (!battle_ctx.battle_ui)
    {
        error_exit(1, "Could not allocate memory for BattleUI");
    }

    battle_ctx.battle_ui->text_box = (Rectangle){
        ui_config.window_margin, screen.height - (ui_config.window_margin + ui_config.text_height),
        screen.width - ui_config.window_margin * 2, ui_config.text_height};

    // TODO: Get consistent asset sizes
    // Set positions for menus and monsters
    battle_ctx.battle_ui->player_mon_pos = (Vector2){screen.width * 0.6f, screen.height * 0.35f};
    battle_ctx.battle_ui->enemy_mon_pos = (Vector2){screen.width * 0.05f, screen.height * 0.1f};
    battle_ctx.battle_ui->action_menu_pos =
        (Vector2){battle_ctx.battle_ui->text_box.x + 20, battle_ctx.battle_ui->text_box.y + 20};
    battle_ctx.battle_ui->status_bar_pos =
        (Vector2){battle_ctx.battle_ui->text_box.x + 20, battle_ctx.battle_ui->text_box.y + 80};

    battle_ctx.state = BATTLE_MENU;

    // Initialize monsters (here froge is hardcoded in)
    if (!battle_ctx.player_mon)
    {
        Result res = create_mon("froge");
        if (res.err)
            error_exit(1, "%s", res.err);

        battle_ctx.player_mon = (Mon *)res.value;
        battle_ctx.player_mon->hp = 100;
        load_mon_texture(battle_ctx.player_mon, BACK);
    }

    if (!battle_ctx.enemy_mon)
    {
        Result res = create_mon("froge");
        if (res.err)
            error_exit(1, "%s", res.err);

        battle_ctx.enemy_mon = (Mon *)res.value;
        battle_ctx.enemy_mon->hp = 80;
        load_mon_texture(battle_ctx.enemy_mon, FRONT);
    }
}

// clang-format off
static void _attack_select() { battle_ctx.state = BATTLE_ATTACK; }
static void _items_select()  { battle_ctx.state = BATTLE_ITEMS; }
static void _run_select()    { battle_ctx.state = BATTLE_RUN; }
static void _switch_select() { battle_ctx.state = BATTLE_SWITCH; }
// clang-format on

/**
 * Initializes values for the top level action menu.
 */
static void _action_menu_create()
{
    const char *item_texts[] = {"ATTACK", "ITEMS", "RUN", "SWITCH"};
    void (*select_callbacks[])(void) = {_attack_select, _items_select, _run_select, _switch_select};
    MenuConfig action_menu_config = {
        .title = "BATTLE MENU",
        .rect = {battle_ctx.battle_ui->text_box.x + battle_ctx.battle_ui->text_box.width * 0.5f +
                     10,
                 battle_ctx.battle_ui->text_box.y + 30, 0, 0},
        .font_size = 20,
        .layout = MENU_LAYOUT_GRID,
        .num_rows = 2,
        .num_cols = 2,
    };

    Result res = menu_create(&action_menu_config, item_texts, select_callbacks, 4);
    if (res.err)
    {
        error_log(res.err);
        return;
    }
    battle_ctx.action_menu = (Menu *)res.value;
}

static void _action_menu_end()
{
    if (battle_ctx.action_menu)
        menu_destroy(battle_ctx.action_menu);

    battle_ctx.action_menu = nullptr;
}

static void _action_menu_display()
{
    if (!battle_ctx.action_menu)
        _action_menu_create();

    // Vertical line between text box and action menu
    DrawLine(battle_ctx.battle_ui->text_box.x + battle_ctx.battle_ui->text_box.width * 0.5f,
             battle_ctx.battle_ui->text_box.y,
             battle_ctx.battle_ui->text_box.x + battle_ctx.battle_ui->text_box.width * 0.5f,
             battle_ctx.battle_ui->text_box.y + battle_ctx.battle_ui->text_box.height, GRAY);

    menu_draw(battle_ctx.action_menu);
    menu_handle_input(battle_ctx.action_menu);
}

static void _render_mon(Mon *mon, Vector2 position)
{
    if (!mon || !IsTextureValid(mon->sprite.texture))
        return;

    DrawTextureEx(mon->sprite.texture, position, ui_config.mon_rotation, ui_config.mon_scale,
                  ui_config.mon_tint);
}

/**
 * Renders text box on the bottom of the screen.
 */
static void _render_text_box(void)
{
    DrawRectangleLines(battle_ctx.battle_ui->text_box.x, battle_ctx.battle_ui->text_box.y,
                       battle_ctx.battle_ui->text_box.width, battle_ctx.battle_ui->text_box.height,
                       WHITE);
}

/**
 * Renders menu on the bottom right of the screen. This menu might be the action menu or
 * one of the submenus depending on the battle state.
 */
static void _render_menu(void)
{
    switch (battle_ctx.state)
    {
    case BATTLE_MENU:
        _action_menu_display();
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

void battle_scene_render(void)
{
    if (!battle_ctx.initialized)
    {
        _init_battle_ui();
        battle_ctx.initialized = true;
    }

    DrawText("Battle scene is active!\nPress B to go back!", 50, 50, 20, DARKGRAY);

    _render_text_box();
    _render_menu();

    if (battle_ctx.player_mon)
        _render_mon(battle_ctx.player_mon, battle_ctx.battle_ui->player_mon_pos);

    if (battle_ctx.enemy_mon)
        _render_mon(battle_ctx.enemy_mon, battle_ctx.battle_ui->enemy_mon_pos);
}

void battle_scene_end(void)
{
    if (battle_ctx.player_mon)
    {
        destroy_mon(battle_ctx.player_mon);
        battle_ctx.player_mon = nullptr;
    }

    if (battle_ctx.enemy_mon)
    {
        destroy_mon(battle_ctx.enemy_mon);
        battle_ctx.enemy_mon = nullptr;
    }

    if (battle_ctx.battle_ui)
    {
        heap_list.free(battle_ctx.battle_ui);
        battle_ctx.battle_ui = nullptr;
    }

    _action_menu_end();
    battle_ctx.state = BATTLE_MENU;
    battle_ctx.initialized = false;
}
