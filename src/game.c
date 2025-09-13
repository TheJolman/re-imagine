/**
 * @file game.c
 * @brief Core game logic implementation
 */

#include <raylib.h>
#include <raymath.h>

#include "battle.h"
#include "game.h"
#include "map.h"
#include "pause.h"

GameContext ctx = {0};

static void _move_player(void)
{
    // Movement
    float moveSpeedModifier = 1.0f;
    if (IsKeyDown(KEY_LEFT_SHIFT))
    {
        moveSpeedModifier = 2.0f;
    }

    ctx.player.speed = ctx.player.base_speed * moveSpeedModifier;
    Vector2 moveDirection = {0.0f, 0.0f};

    if (IsKeyDown(KEY_W))
        moveDirection.y -= 1.0f;
    if (IsKeyDown(KEY_S))
        moveDirection.y += 1.0f;
    if (IsKeyDown(KEY_A))
        moveDirection.x -= 1.0f;
    if (IsKeyDown(KEY_D))
        moveDirection.x += 1.0f;

    if (moveDirection.x != 0.0f || moveDirection.y != 0.0f)
    {
        moveDirection = Vector2Normalize(moveDirection);
    }

    // Calculate new position
    Vector2 newPosition = {ctx.player.position.x + moveDirection.x * ctx.player.speed,
                           ctx.player.position.y + moveDirection.y * ctx.player.speed};

    ctx.player.position = newPosition;

    // Camera
    ctx.camera.target = ctx.player.position;
}

static void _handle_input(void)
{
    switch (ctx.state)
    {
    case FREE_ROAM:
        _move_player();
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
    ctx.state = FREE_ROAM;

    ctx.player.position = (Vector2){(float)screen.width / 2, (float)screen.height / 2};
    ctx.player.base_speed = 5.0f;
    ctx.player.speed = ctx.player.base_speed;
    ctx.player.size = 30;

    ctx.camera.target = ctx.player.position;
    ctx.camera.offset = (Vector2){screen.width / 2.0f, screen.height / 2.0f};
    ctx.camera.zoom = 1.0f;
}

void game_update(void) { _handle_input(); }

void draw_game(Map *map)
{
    BeginDrawing();
    ClearBackground(BLACK);

    switch (ctx.state)
    {
    case FREE_ROAM:
        BeginMode2D(ctx.camera);

        map_draw(map);
        // Draw player
        DrawCircleV(ctx.player.position, ctx.player.size / 2, RED);

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

    EndDrawing();
}

void game_cleanup(void) {}
