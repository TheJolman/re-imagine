#include <raylib.h>
#include <stdint.h>
#include <stdlib.h>

#include "game.h"

// ==== Configuration ====
// Window
constexpr uint32_t window_width = 960;
constexpr uint32_t window_height = 540;
constexpr char window_title[] = "Re-Imagine";
constexpr uint32_t fps_target = 540;

void _game_draw() {
    BeginDrawing();
    ClearBackground(BLACK);
#ifdef DEBUG
    DrawFPS(10, 10);
#endif

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
        _game_draw();
    }
    CloseWindow();

    return EXIT_SUCCESS;
}
