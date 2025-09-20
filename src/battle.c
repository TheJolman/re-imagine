/**
 * @file battle.c
 * @brief Battle system implementation
 * Note that 'action_menu' refers to the top-level menu that includes 'attack', 'items', 'run', and
 * 'switch' options.
 */

#include "battle.h"
#include "game.h"
#include "menu.h"
#include "raylib.h"

// TODO: Enforce a minimum screen size
static constexpr BattleUIConfig cfg = {
    .window_margin = 50,
    .text_height = 150,
    .mon_tint = WHITE,
    .mon_rotation = 0.0,
    .mon_scale = 0.4f,

    .player_mon_x_margin = 50.0f,
    .player_mon_y_margin = 200.0f, // to be above text box
    .enemy_mon_x_margin = 50.0f,
    .enemy_mon_y_margin = 100.0f,

    .action_menu_pos_offset = {20, 20},
    .status_bar_pos_offset = {20, 80},
    .action_menu_split_x_percent = 0.5f,
    .action_menu_rect_offset = {15, 45},
    .action_menu_font_size = 20,
};

static BattleContext ctx = {0};

// ------------------------ Top level battle menu callbacks ------------------------ //
static void _attack_select() { ctx.state = BATTLE_ATTACK; }
static void _items_select() { ctx.state = BATTLE_ITEMS; }
static void _run_select()
{
    battle_scene_end();
    game_set_state(FREE_ROAM);
}
static void _switch_select() { ctx.state = BATTLE_SWITCH; }
// ------------------------ Top level battle menu callbacks ------------------------ //


/**
 * @brief Calculates the layout of UI elements based on the current window size.
 * This should be called every frame to ensure the UI is responsive.
 */
static void _update_battle_layout(void)
{
    ctx.battle_ui->text_box =
        (Rectangle){cfg.window_margin, GetScreenHeight() - (cfg.window_margin + cfg.text_height),
                    GetScreenWidth() - cfg.window_margin * 2, cfg.text_height};

    // Calculate monster positions, accounting for sprite dimensions to respect margins
    if (ctx.player_mon)
    {
        // Calculated from bottom right of screen
        float player_w = ctx.player_mon->sprite.texture.width * cfg.mon_scale;
        float player_h = ctx.player_mon->sprite.texture.height * cfg.mon_scale;
        ctx.player_mon->position =
            (Vector2){GetScreenWidth() - cfg.player_mon_x_margin - player_w,
                      GetScreenHeight() - cfg.player_mon_y_margin - player_h};
    }

    if (ctx.enemy_mon)
    {
        // Calculated from top-left corner of screen
        ctx.enemy_mon->position = (Vector2){cfg.enemy_mon_x_margin, cfg.enemy_mon_y_margin};
    }

    ctx.battle_ui->action_menu_pos =
        (Vector2){ctx.battle_ui->text_box.x + cfg.action_menu_pos_offset.x,
                  ctx.battle_ui->text_box.y + cfg.action_menu_pos_offset.y};
    ctx.battle_ui->status_bar_pos =
        (Vector2){ctx.battle_ui->text_box.x + cfg.status_bar_pos_offset.x,
                  ctx.battle_ui->text_box.y + cfg.status_bar_pos_offset.y};
}

/**
 * Initializes values for the top level action menu.
 */
static void _action_menu_create(const char *title, const char **item_texts,
                                void (*select_callbacks[4])(void))
{
    MenuConfig action_menu_config = {
        .title = title,
        .rect = {ctx.battle_ui->text_box.x +
                     ctx.battle_ui->text_box.width * cfg.action_menu_split_x_percent +
                     cfg.action_menu_rect_offset.x,
                 ctx.battle_ui->text_box.y + cfg.action_menu_rect_offset.y, 0, 0},
        .font_size = cfg.action_menu_font_size,
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
    ctx.action_menu = (Menu *)res.value;
}

/**
 * @brief Performs one-time initialization for the battle scene.
 * Loads monster assets into memory and sets the initial state of the battle.
 */
static void _init_battle_state(void)
{
    ctx.battle_ui = heap_list.malloc(sizeof(BattleUILayout));
    if (!ctx.battle_ui)
    {
        error_exit(1, "Could not allocate memory for BattleUI");
    }

    ctx.state = BATTLE_MENU;

    // Initialize monsters (here froge is hardcoded in)
    if (!ctx.player_mon)
    {
        Result res = create_mon("froge");
        if (res.err)
            error_exit(1, "%s", res.err);

        ctx.player_mon = (Mon *)res.value;
        ctx.player_mon->health = (Health){100, 100};
        load_mon_texture(ctx.player_mon, BACK);
    }

    if (!ctx.enemy_mon)
    {
        Result res = create_mon("froge");
        if (res.err)
            error_exit(1, "%s", res.err);

        ctx.enemy_mon = (Mon *)res.value;
        ctx.enemy_mon->health = (Health){100, 100};
        load_mon_texture(ctx.enemy_mon, FRONT);
    }

    // Initialize action menu
    const char *title = "WHAT WILL YOU DO?";

    const char *item_texts[4] = {"ATTACK", "ITEMS", "RUN", "SWITCH"};
    void (*select_callbacks[])(void) = {_attack_select, _items_select, _run_select, _switch_select};
    _action_menu_create(title, item_texts, select_callbacks);
}

static void _action_menu_end()
{
    if (ctx.action_menu)
        menu_destroy(ctx.action_menu);

    ctx.action_menu = nullptr;
}

static void _action_menu_display()
{
    // Box at bottom of screen
    DrawRectangleLines(ctx.battle_ui->text_box.x, ctx.battle_ui->text_box.y,
                       ctx.battle_ui->text_box.width, ctx.battle_ui->text_box.height, WHITE);
    // Vertical line that divides box into text box and action menu box
    DrawLine(ctx.battle_ui->text_box.x + ctx.battle_ui->text_box.width * 0.5f,
             ctx.battle_ui->text_box.y,
             ctx.battle_ui->text_box.x + ctx.battle_ui->text_box.width * 0.5f,
             ctx.battle_ui->text_box.y + ctx.battle_ui->text_box.height, GRAY);

    // Update menu position every frame to ensure it is responsive
    ctx.action_menu->config.rect =
        (Rectangle){ctx.battle_ui->text_box.x +
                        ctx.battle_ui->text_box.width * cfg.action_menu_split_x_percent +
                        cfg.action_menu_rect_offset.x,
                    ctx.battle_ui->text_box.y + cfg.action_menu_rect_offset.y, 0, 0};

    // Recalculate item positions based on the new rect
    menu_update_layout(ctx.action_menu);

    menu_draw(ctx.action_menu);
    menu_handle_input(ctx.action_menu);
}

static void _render_mon(Mon *mon)
{
    if (!mon || !IsTextureValid(mon->sprite.texture))
        return;

    DrawTextureEx(mon->sprite.texture, mon->position, cfg.mon_rotation, cfg.mon_scale,
                  cfg.mon_tint);
}

/**
 * Renders menu on the bottom right of the screen. This menu might be the action menu or
 * one of the submenus depending on the battle state.
 */
static void _render_menu(void)
{
    switch (ctx.state)
    {
    case BATTLE_MENU:
        _action_menu_display();
        break;
    case BATTLE_ATTACK:
        // _attack_menu_display();
        break;
    case BATTLE_ITEMS:
        // _items_menu_display();
        break;
    case BATTLE_SWITCH:
        // _switch_menu_display();
        break;
    }
}

void battle_scene_render(void)
{
    if (!ctx.initialized)
    {
        _init_battle_state();
        ctx.initialized = true;
    }

    _update_battle_layout();

    DrawText("Battle scene is active!\nPress B to go back!", 50, 50, 20, DARKGRAY);

    _render_menu();

    if (ctx.player_mon)
        _render_mon(ctx.player_mon);

    if (ctx.enemy_mon)
        _render_mon(ctx.enemy_mon);
}

void battle_scene_end(void)
{
    if (ctx.player_mon)
    {
        destroy_mon(ctx.player_mon);
        ctx.player_mon = nullptr;
    }

    if (ctx.enemy_mon)
    {
        destroy_mon(ctx.enemy_mon);
        ctx.enemy_mon = nullptr;
    }

    if (ctx.battle_ui)
    {
        heap_list.free(ctx.battle_ui);
        ctx.battle_ui = nullptr;
    }

    _action_menu_end();
    ctx.state = BATTLE_MENU;
    ctx.initialized = false;
}
