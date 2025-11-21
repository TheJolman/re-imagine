#include "map.h"
#include "debug.h"
#include "raylib.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Result map_load(const char *map_name)
{
    char csv_path[256];
    snprintf(csv_path, sizeof(csv_path), "assets/maps/%s/map.csv", map_name);
    FILE *file = fopen(csv_path, "r");
    if (!file)
    {
        char err[256];
        snprintf(err, sizeof(err), "could not open file: %s", csv_path);
        return (Result){.value = nullptr, .err = err};
    }

    debug_log("Map file %s opened successfully", csv_path);

    char tileset_path[256];
    snprintf(tileset_path, sizeof(tileset_path), "assets/maps/%s/sprite.png", map_name);
    Texture2D tileset = LoadTexture(tileset_path);
    if (tileset.id == 0)
    {
        fclose(file);
        char err[256];
        snprintf(err, sizeof(err), "could not load tileset: %s", tileset_path);
        return (Result){.value = nullptr, .err = err};
    }
    debug_log("Tileset %s loaded successfully", tileset_path);

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
    debug_log("File %s read from and closed.", csv_path);

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
    map->tileset = tileset;

    return (Result){.value = map, .err = nullptr};
}

void map_destroy(Map *map)
{
    UnloadTexture(map->tileset);
    heap_list.free(map->data);
    heap_list.free(map);
    map = nullptr;
}

void map_draw(Map *map)
{
    constexpr uint32_t TILE_SIZE_IN_TEXTURE = 16;

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
            int16_t tile_id = map->data[y * map->width + x];

            Rectangle source = {.x = tile_id * TILE_SIZE_IN_TEXTURE,
                                .y = 0,
                                .width = TILE_SIZE_IN_TEXTURE,
                                .height = TILE_SIZE_IN_TEXTURE};

            Rectangle dest = {.x = x * MAP_TILE_SIZE,
                              .y = y * MAP_TILE_SIZE,
                              .width = MAP_TILE_SIZE,
                              .height = MAP_TILE_SIZE};

            DrawTexturePro(map->tileset, source, dest, (Vector2){0, 0}, 0.0f, WHITE);
        }
    }
}
