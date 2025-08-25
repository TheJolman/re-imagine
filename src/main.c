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
#include <tmx.h>

#include "debug.h"
#include "game.h"
#include "map.h"

#define VERSION "0.0.1"

constexpr size_t screen_width = 1200;
constexpr size_t screen_height = 900;

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
            fputs("ERROR: Unrecognized argument: ", stderr);
            fputs(argv[i], stderr);
            fputc('\n', stderr);
            exit(1);
        }
    }

    screen.width = screen_width;
    screen.height = screen_height;

    debug_log("Game initiated with screen dimensions %dx%d", screen.width, screen.height);

    // tmx_img_load_func = raylib_tex_loader;
    // tmx_img_free_func = raylib_free_tex;
    //
    // char mapPath[] = "resources/island.tmx";
    // tmx_map *map = tmx_load(mapPath);

    InitWindow(screen.width, screen.height, "Game!");
    SetTargetFPS(60);
    InitGame();

    // Main game loop
    while (true)
    {
        UpdateGame();
        DrawGame(/* map */);
    }

    // tmx_map_free(map);
    CloseWindow();

    return 0;
}
