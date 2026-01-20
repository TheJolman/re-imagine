#include <raylib.h>
#include <stdint.h>
#include <stdlib.h>

#include "game.h"
#include "player.h"

// ==== Configuration ====
// Window
constexpr uint32_t window_width = 960;
constexpr uint32_t window_height = 540;
constexpr char window_title[] = "Re-Imagine";
constexpr uint32_t fps_target = 60;
constexpr float camera_base_zoom = 1.0f;

// Global game context
GameContext g_ctx = {};

/** Initializes game objects and memory
 */
static void _game_init() {
    g_ctx.frame_arena = arena_init(1024 * 1024); // 1MB
    g_ctx.state = FREE_ROAM;
    player_init();
    g_ctx.camera.target = g_ctx.player.position;
    g_ctx.camera.zoom = camera_base_zoom;
    // only called once since window doesn't resize
    g_ctx.camera.offset = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
}

/** Stuff cleaned up before CloseWindow() is called
 */
static void _game_cleanup() {
    player_cleanup();
    arena_free(&g_ctx.frame_arena);
}

static void _input_handler() {
    switch (g_ctx.state) {
    case FREE_ROAM:
        player_move();
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

static void _game_draw() {
    BeginDrawing();
    ClearBackground(BLACK);

    switch (g_ctx.state) {
    case FREE_ROAM:
        BeginMode2D(g_ctx.camera);
        // map_draw(g_ctx.map);
        player_draw();

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

#ifdef DEBUG
    DrawFPS(10, 10);
#endif
    EndDrawing();
}

/**
 * Initializes window and run main game loop. Intended to be called from main()
 */
int game_run() {
    InitWindow(window_width, window_height, window_title);
    SetWindowMinSize(window_width, window_height);
    if (!IsWindowReady()) {
        TraceLog(LOG_FATAL, "failed to initialize window");
        return EXIT_FAILURE;
    }
    SetTargetFPS(fps_target);
    SetExitKey(KEY_NULL);

    _game_init();

    while (!WindowShouldClose()) {
        arena_reset(&g_ctx.frame_arena);
        _input_handler();
        _game_draw();
    }

    _game_cleanup();
    CloseWindow();

    return EXIT_SUCCESS;
}
