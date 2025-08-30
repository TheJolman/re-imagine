#pragma once

#include "stdint.h"
#include "utils.h"
#include <raylib.h>

typedef struct
{
    int width;
    int height;
} Screen;

extern Screen screen;

constexpr uint32_t MAP_MAX_ROWS = 100;
constexpr uint32_t MAP_MAX_COLS = 100;
constexpr uint32_t MAP_TILE_SIZE = 80;

typedef struct
{
    uint32_t height;
    uint32_t width;
    int *data; // use 1D array for simple memory management
} Map;

Result map_load_from_csv(const char *file_path);
void map_draw(Map *map);
