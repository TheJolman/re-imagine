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

typedef struct
{
    uint32_t height;
    uint32_t width;
    int *data[];
} Map;

Result map_load_from_csv(const char *file_path);
