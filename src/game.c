#include <raylib.h>
#include <stdint.h>
#include <stdlib.h>

#include "game.h"

// ==== Configuration ====
// Window
constexpr uint32_t window_width = 960;
constexpr uint32_t window_height = 540;
constexpr char window_title[] = "Re-Imagine";
constexpr uint32_t fps_target = 60;

// Global game context
GameContext g_ctx = {};

void _input_handler() {
    switch (g_ctx.state) {
    case FREE_ROAM:
        // player_move();
        if (IsKeyPressed(KEY_B))
            g_ctx.state = BATTLE_SCENE;
        if (IsKeyPressed(KEY_ESCAPE))
            g_ctx.state = PAUSED;
        break;

    case BATTLE_SCENE:
        if (IsKeyPressed(KEY_B)) {
            // battle_scene_end();
            g_ctx.state = FREE_ROAM;
        }
        break;

    case PAUSED:
        if (IsKeyPressed(KEY_ESCAPE)) {
            // pause_menu_end();
            g_ctx.state = FREE_ROAM;
        }
        break;

    case TITLE_SCREEN:
        break;
    }
}

void _game_draw() {
    BeginDrawing();
    ClearBackground(BLACK);
#ifdef DEBUG
    DrawFPS(10, 10);
#endif

    switch (g_ctx.state) {

    case FREE_ROAM:
        BeginMode2D(g_ctx.camera);
        // UpdatePlayerDrawFrame();
        // map_draw(g_ctx.map);
        // player_draw();

        EndMode2D();
        DrawText("Press B to enter the Battle Scene!", 50, 50, 20, RAYWHITE);
        break;
    case BATTLE_SCENE:
        // battle_scene_render();
        break;
    case PAUSED:
        // pause_menu_display();
        break;
    case TITLE_SCREEN:
        break;
    }

    EndDrawing();
}

int game_run() {
    InitWindow(window_width, window_height, window_title);
    SetWindowMinSize(window_width, window_height);
    if (!IsWindowReady()) {
        TraceLog(LOG_FATAL, "failed to initialize window");
        return EXIT_FAILURE;
    }
    SetTargetFPS(fps_target);
    SetExitKey(KEY_NULL);

    while (!WindowShouldClose()) {
        _input_handler();
        _game_draw();
    }
    CloseWindow();

    return EXIT_SUCCESS;
}
