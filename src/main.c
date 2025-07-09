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
#include <tmx.h>

#include "debug.h"
#include "game.h"
#include "map.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

Screen screen = {0};

int main(void)
{
    screen.width = SCREEN_WIDTH;
    screen.height = SCREEN_HEIGHT;

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
