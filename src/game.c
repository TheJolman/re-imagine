/**
 * @file game.c
 * @brief Core game logic implementation
 */

#include <raylib.h>
#include <raymath.h>

#include "battle.h"
#include "debug.h"
#include "game.h"
#include "map.h"
#include "pause.h"
#include "player.h"

// Global game context I think it shouldnt be static
GameContext Game_ctx = {0};

static void _game_input_handler(void)
{
    switch (Game_ctx.state)
    {
    case FREE_ROAM:
        _player_move();
        if (IsKeyPressed(KEY_B))
            Game_ctx.state = BATTLE_SCENE;
        if (IsKeyPressed(KEY_ESCAPE))
            Game_ctx.state = PAUSED;
        break;

    case BATTLE_SCENE:
        if (IsKeyPressed(KEY_B))
        {
            // NOTE: If concurencey is ever added should these be switched?
            battle_scene_end();
            Game_ctx.state = FREE_ROAM;
        }
        break;

    case PAUSED:
        if (IsKeyPressed(KEY_ESCAPE))
        {
            pause_menu_end();
            Game_ctx.state = FREE_ROAM;
        }
        break;

    case TITLE_SCREEN:
        break;
    }

    // Unconditional inputs
    if (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT))
    {
        if (IsKeyPressed(KEY_F4))
            CloseWindow();
    }
}

void game_init(void)
{
    create_player_sprite_animation();

    const char *file_path = "assets/map.csv";
    Result res = map_load_from_csv(file_path);
    if (res.err)
    {
        error_exit(1, "%s", res.err);
    }
    Game_ctx.map = (Map *)res.value;
    debug_log("Map loaded with %u rows and %u cols", Game_ctx.map->height, Game_ctx.map->width);

    Game_ctx.state = FREE_ROAM;

    Game_ctx.player.position = Game_cfg.player_initial_pos;
    Game_ctx.player.velocity.max_speed = Game_cfg.player_base_speed;
    Game_ctx.player.size = Game_cfg.player_size;

    Game_ctx.player.sprite.rotation = 0.0f;
    Game_ctx.player.sprite.tint = WHITE;
    Game_ctx.player.sprite.scale = 1.0f;

    Game_ctx.camera.target = Game_ctx.player.position;
    // camera offset set in game_draw to handle window resizing
    Game_ctx.camera.zoom = Game_cfg.camera_base_zoom;
}

void game_update(void) { _game_input_handler(); }

void game_draw()
{
    BeginDrawing();
    ClearBackground(BLACK);

    // Update camera offset each frame to handle window resizing
    Game_ctx.camera.offset = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};

    switch (Game_ctx.state)
    {
    case FREE_ROAM:
        BeginMode2D(Game_ctx.camera);
        // UpdatePlayerDrawFrame();
        map_draw(Game_ctx.map);
        _player_draw();

        EndMode2D();
        DrawText("Press B to enter the Battle Scene!", 50, 50, 20, DARKGRAY);
        break;
    case BATTLE_SCENE:
        battle_scene_render();
        break;
    case PAUSED:
        pause_menu_display();
        break;
    case TITLE_SCREEN:
        break;
    }

#ifdef DEBUG
    DrawFPS(10, 10);
#endif

    EndDrawing();
}

void game_cleanup(void) { map_destroy(Game_ctx.map); }
