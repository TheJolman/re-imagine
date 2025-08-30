#pragma once

#include <raylib.h>
#include "utils.h"
#include "stdint.h"

typedef struct
{
    int width;
    int height;
} Screen;

extern Screen screen;

constexpr uint32_t MAP_MAX_ROWS = 100;
constexpr uint32_t MAP_MAX_COLS = 100;

typedef struct
{
    uint32_t height;
    uint32_t width;
    int *data; // use 1D array for simple memory management
} Map;

Result map_load_from_csv(const char *file_path);
