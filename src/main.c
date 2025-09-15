/*******************************************************************************************
 *
 *   VGDC Game Project
 *
 *   <Game title>
 *   <Game description>
 *
 *   This game has been created using raylib (www.raylib.com)
 *
 *   Copyright (c) 2025 Joshua Holman
 *
 ********************************************************************************************/

/**
 * @file main.c
 * @brief Main entry point and window initialization
 */

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "game.h"
#include "utils.h"

#ifndef GIT_VERSION
#define GIT_VERSION "unknown"
#endif

static constexpr struct
{
    size_t screen_width_initial;
    size_t screen_height_initial;
    size_t screen_width_min;
    size_t screen_height_min;
    size_t fps_target;
} cfg = {1200, 900, 400, 300, 60};

/**
 * @returns true if target matches short_arg or long_arg.
 * @returns false otherwise
 * If only short_arg or long_arg is needed, pass nullptr in place of the other.
 */
static bool _match_arg(const char *target, const char *short_arg, const char *long_arg)
{
    return (short_arg && strcmp(target, short_arg) == 0 ||
            long_arg && strcmp(target, long_arg) == 0);
}

int main(int argc, const char **argv)
{
    // ----------- Command line argument parsing -----------
    for (int i = 1; i < argc; i++)
    {
        if (_match_arg(argv[i], "-v", "--version"))
        {
            printf("%s %s\n", argv[0], GIT_VERSION);
            exit(0);
        }
        else if (_match_arg(argv[i], "-h", "--help"))
        {
            printf("Usage: %s [-h | --help] [-v | --version]\n"
                   "Have fun!\n",
                   argv[0]);
            exit(0);
        }
        else
        {
            error_exit(1,
                       "Unrecognized argument. "
                       "Try '%s --help' for usage information.",
                       argv[0]);
        }
    }

    // ----------- Game related stuff starts here -----------

    heap_list = heap_list_create();
    atexit(free_all);

    SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(cfg.screen_width_initial, cfg.screen_height_initial, "Game!");
    SetWindowMinSize(cfg.screen_width_min, cfg.screen_height_min);

    if (!IsWindowReady())
    {
        error_exit(1, "failed to initialize window");
    }

    debug_log("Game initiated with screen dimensions %dx%d", cfg.screen_width_initial,
              cfg.screen_height_initial);

    SetTargetFPS(cfg.fps_target);
    SetExitKey(KEY_NULL);

    game_init();

    // Main game loop
    while (!WindowShouldClose())
    {
        game_update();
        game_draw();
    }

    game_cleanup();

    CloseWindow();
    return 0;
}
