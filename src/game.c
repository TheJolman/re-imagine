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

static constexpr GameConfig cfg = {
    .player_base_speed = 5.0f,
    .player_sprint_modifier = 2.0f,
    .player_initial_pos = (Vector2){100, 100},
    .player_size = 30,
    .camera_base_zoom = 1.0f,
};

static GameContext ctx = {0};

static void _player_move(void)
{
    // Determine base speed and apply sprint modifier
    float current_speed = cfg.player_base_speed;
    if (IsKeyDown(KEY_LEFT_SHIFT))
    {
        current_speed *= cfg.player_sprint_modifier;
    }

    // Get movement direction from input
    Vector2 move_vector = {0};
    if (IsKeyDown(KEY_W))
        move_vector.y -= 1.0f;
    if (IsKeyDown(KEY_S))
        move_vector.y += 1.0f;
    if (IsKeyDown(KEY_A))
        move_vector.x -= 1.0f;
    if (IsKeyDown(KEY_D))
        move_vector.x += 1.0f;

    if (Vector2Length(move_vector) > 0.0f)
    {
        // Normalize the vector to get a pure direction, then scale by speed
        move_vector = Vector2Normalize(move_vector);
        ctx.player.velocity.vec = Vector2Scale(move_vector, current_speed);
        ctx.player.position = Vector2Add(ctx.player.position, ctx.player.velocity.vec);
    }
    else
    {
        // No movement input, so velocity is zero
        ctx.player.velocity.vec = (Vector2){0};
    }

    // Camera always follows the player's position
    ctx.camera.target = ctx.player.position;
}

static void _player_draw(void)
{
    // Draw player
    Vector2 sprite_center = {
        (float)ctx.player.sprite.texture.width * ctx.player.sprite.scale / 2.0f,
        (float)ctx.player.sprite.texture.height * ctx.player.sprite.scale / 2.0f,
    };
    DrawTextureEx(ctx.player.sprite.texture, Vector2Subtract(ctx.player.position, sprite_center),
                  ctx.player.sprite.rotation, ctx.player.sprite.scale, ctx.player.sprite.tint);
#ifdef DEBUG
    DrawLine((int)ctx.camera.target.x, -GetScreenHeight() * 10, (int)ctx.camera.target.x,
             GetScreenHeight() * 10, ORANGE);
    DrawLine(-GetScreenWidth() * 10, (int)ctx.camera.target.y, GetScreenWidth() * 10,
             (int)ctx.camera.target.y, ORANGE);
#endif
}

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

void game_cleanup(void) { map_destroy(ctx.map); }
