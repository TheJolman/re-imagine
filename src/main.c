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

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "debug.h"
#include "game.h"
#include "map.h"

#define VERSION "0.0.1"

uint32_t screen_width = 1200;
uint32_t screen_height = 900;

Screen screen = {0};

/**
 * @returns true if target matches short_arg or long_arg.
 * @returns false otherwise
 * If only short_arg or long_arg is needed, pass nullptr in place of the other.
 */
bool match_arg(const char *target, const char *short_arg, const char *long_arg)
{
    return (short_arg && strcmp(target, short_arg) == 0 ||
            long_arg && strcmp(target, long_arg) == 0);
}

int main(int argc, const char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        if (match_arg(argv[i], "-v", "--version"))
        {
            printf("%s v%s\n", argv[0], VERSION);
            exit(0);
        }
        else if (match_arg(argv[i], "-h", "--help"))
        {
            printf("Usage: %s [-h | --help] [-v | --version]\n"
                   "Have fun!\n",
                   argv[0]);
            exit(0);
        }
        else
        {
            fprintf(stderr,
                    "ERROR: Unrecognized argument."
                    "Try '%s --help' for usage information.",
                    argv[0]);
            exit(1);
        }
    }

    screen.width = screen_width;
    screen.height = screen_height;

    debug_log("Game initiated with screen dimensions %dx%d", screen.width, screen.height);

    InitWindow(screen.width, screen.height, "Game!");
    if (!IsWindowReady())
    {
        fputs("Failed to initialize window\n", stderr);
        exit(1);
    }
    SetTargetFPS(60);
    InitGame();
    SetExitKey(KEY_NULL);

    // Main game loop
    while (!WindowShouldClose())
    {
        UpdateGame();
        DrawGame();
    }

    CloseWindow();
    return 0;
}
