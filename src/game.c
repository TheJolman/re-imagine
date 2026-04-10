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

constexpr PlayerConfig player_cfg = {
    .base_speed = 5.0f,
    .sprint_modifier = 2.0f,
    .init_position = (Position){100, 100},
    .size = 30, // collider size
};

/** Initializes game objects and memory
 */
static void _game_init(GameContext *ctx) {
    ctx->frame_arena = arena_init(1024 * 1024); // 1MB
    ctx->state = FREE_ROAM;
    player_init(&ctx->player, &player_cfg);
    ctx->camera.target = ctx->player.position;
    ctx->camera.zoom = camera_base_zoom;
    // only called once since window doesn't resize
    ctx->camera.offset = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
}

/** Stuff cleaned up before CloseWindow() is called
 */
static void _game_cleanup(GameContext *ctx) {
    player_cleanup(&ctx->player);
    arena_free(&ctx->frame_arena);
}

static void _input_handler(GameContext *ctx) {
    switch (ctx->state) {
    case FREE_ROAM:
        player_move(&ctx->player, &ctx->camera);
        if (IsKeyPressed(KEY_B))
            ctx->state = BATTLE_SCENE;
        if (IsKeyPressed(KEY_ESCAPE))
            ctx->state = PAUSED;
        break;

    case BATTLE_SCENE:
        if (IsKeyPressed(KEY_B)) {
            // battle_scene_end();
            ctx->state = FREE_ROAM;
        }
        break;

    case PAUSED:
        if (IsKeyPressed(KEY_ESCAPE)) {
            // pause_menu_end();
            ctx->state = FREE_ROAM;
        }
        break;

    case TITLE_SCREEN:
        break;
    }
}

static void _game_draw(const GameContext *ctx) {
    BeginDrawing();
    ClearBackground(BLACK);

    switch (ctx->state) {
    case FREE_ROAM:
        BeginMode2D(ctx->camera);
        // map_draw(g_ctx.map);
        player_draw(&ctx->player);

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

    _game_init(&g_ctx);

    while (!WindowShouldClose()) {
        arena_reset(&g_ctx.frame_arena);
        _input_handler(&g_ctx);
        _game_draw(&g_ctx);
    }

    _game_cleanup(&g_ctx);
    CloseWindow();

    return EXIT_SUCCESS;
}
