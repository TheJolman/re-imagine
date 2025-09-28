/**
 * @file game.c
 * @brief Core game logic implementation
 */

#include <raylib.h>
#include <raymath.h>

#include "battle.h"
#include "debug.h"
#include "game.h"
#include "player.h"
#include "map.h"
#include "pause.h"




// Global game context I think it shouldnt be static
GameContext ctx = {0};





static void _game_input_handler(void)
{
    switch (ctx.state)
    {
    case FREE_ROAM:
        _player_move();
        if (IsKeyPressed(KEY_B))
            ctx.state = BATTLE_SCENE;
        if (IsKeyPressed(KEY_ESCAPE))
            ctx.state = PAUSED;
        break;

    case BATTLE_SCENE:
        if (IsKeyPressed(KEY_B))
        {
            // NOTE: If concurencey is ever added should these be switched?
            battle_scene_end();
            ctx.state = FREE_ROAM;
        }
        break;

    case PAUSED:
        if (IsKeyPressed(KEY_ESCAPE))
        {
            pause_menu_end();
            ctx.state = FREE_ROAM;
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
    //CreatePlayerSpriteAnimation();
    CreatePlayerSpriteAnimation();
    
    const char *file_path = "assets/map.csv";
    Result res = map_load_from_csv(file_path);
    if (res.err)
    {
        error_exit(1, "%s", res.err);
    }
    ctx.map = (Map *)res.value;
    debug_log("Map loaded with %u rows and %u cols", ctx.map->height, ctx.map->width);

    ctx.state = FREE_ROAM;

    ctx.player.position = cfg.player_initial_pos;
    ctx.player.velocity.max_speed = cfg.player_base_speed;
    ctx.player.size = cfg.player_size;

    ctx.player.sprite.texture = LoadTexture("assets/sample-assets/Texture/player-cropped.png");
    ctx.player.sprite.rotation = 0.0f;
    ctx.player.sprite.tint = WHITE;
    ctx.player.sprite.scale = 1.0f;

    ctx.camera.target = ctx.player.position;
    // camera offset set in game_draw to handle window resizing
    ctx.camera.zoom = cfg.camera_base_zoom;
}

void game_update(void) { _game_input_handler(); }

void game_draw()
{
    BeginDrawing();
    ClearBackground(BLACK);
    
    // Update camera offset each frame to handle window resizing
    ctx.camera.offset = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};

    switch (ctx.state)
    {
    case FREE_ROAM:
        BeginMode2D(ctx.camera);
        //UpdatePlayerDrawFrame();
        map_draw(ctx.map);
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

void game_set_state(GameState state) { ctx.state = state; }

void game_cleanup(void) { map_destroy(ctx.map); }
