#include "map.h"
#include "debug.h"
#include "raylib.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Result map_load_from_csv(const char *file_path)
{
    FILE *file = fopen(file_path, "r");
    if (!file)
    {
        char err[256];
        snprintf(err, sizeof(err), "could not open file: %s", file_path);
        return (Result){.value = nullptr, .err = err};
    }

    debug_log("Map file %s opened successfully", file_path);

    int16_t temp_data[MAP_MAX_ROWS][MAP_MAX_COLS] = {};
    char line[1024];
    uint32_t row = 0;
    uint32_t max_cols = 0;
    while (fgets(line, sizeof(line), file) && row < MAP_MAX_ROWS)
    {
        uint32_t col = 0;

        char *token = strtok(line, ",");
        while (token != nullptr && col < MAP_MAX_COLS)
        {
            temp_data[row][col] = atoi(token);
            token = strtok(nullptr, ",");
            col++;
        }
        max_cols = col > max_cols ? col : max_cols;
        row++;
    }

    fclose(file);
    debug_log("File %s read from and closed.", file_path);

    Map *map = heap_list.malloc(sizeof(Map *));

    if (!map)
        return (Result){.value = nullptr, .err = "failed to allocate memory for map"};

    map->data = heap_list.malloc(row * max_cols * sizeof(int16_t));
    if (!map->data)
    {
        return (Result){.value = nullptr, .err = "failed to allocate memory for map->data"};
    }

    for (uint32_t y = 0; y < row; y++)
    {
        for (uint32_t x = 0; x < max_cols; x++)
        {
            // accessing 1D array as if it were 2D
            map->data[y * max_cols + x] = temp_data[y][x];
        }
    }
    debug_log("copied data successfully");

    map->height = row;
    map->width = max_cols;

    return (Result){.value = map, .err = nullptr};
}

void map_destroy(Map *map)
{
    heap_list.free(map->data);
    heap_list.free(map);
    map = nullptr;
}

void map_draw(Map *map)
{
    for (uint32_t y = 0; y < map->height; y++)
    {
#ifdef DEBUG // debug grid
        DrawLine(0, y * MAP_TILE_SIZE, map->width * MAP_TILE_SIZE, y * MAP_TILE_SIZE, RED);
#endif
        for (uint32_t x = 0; x < map->width; x++)
        {
#ifdef DEBUG // debug grid
            DrawLine(x * MAP_TILE_SIZE, 0, x * MAP_TILE_SIZE, map->height * MAP_TILE_SIZE, RED);
#endif
            Color color = {};
            // TODO: Replace this with a tileset
            switch (map->data[y * map->width + x])
            {
            case 0:
                color = BROWN;
                break;
            case 1:
                color = GREEN;
                break;
            case 2:
                color = BLUE;
                break;
            case 3: 
                color = RED;
                break;
            default:
                color = WHITE;
                break;
            }
            Rectangle rec = (Rectangle){.x = x * MAP_TILE_SIZE,
                                        .y = y * MAP_TILE_SIZE,
                                        .width = MAP_TILE_SIZE,
                                        .height = MAP_TILE_SIZE};
            DrawRectangleRec(rec, color);
        }
    }
}
