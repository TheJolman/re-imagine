/**
 * @file map.h
 * @brief Map system and tile rendering functionality
 */

#pragma once

#include "stdint.h"
#include "utils.h"
#include <raylib.h>

typedef uint32_t Pixels;

/**
 * @brief Screen dimensions structure
 */
typedef struct
{
    Pixels width;  ///< Screen width in pixels
    Pixels height; ///< Screen height in pixels
} Screen;

constexpr uint32_t MAP_MAX_ROWS = 100; ///< Maximum number of map rows
constexpr uint32_t MAP_MAX_COLS = 100; ///< Maximum number of map columns
constexpr uint32_t MAP_TILE_SIZE = 80; ///< Size of each tile in pixels

/**
 * @brief Map data structure for tile-based rendering
 */
typedef struct
{
    uint32_t height; ///< Map height in tiles
    uint32_t width;  ///< Map width in tiles
    int16_t *data;   ///< 1D array of tile data for simple memory management
} Map;

/**
 * @brief Loads map data from a CSV file
 *
 * @param file_path Path to the CSV file containing map data
 * @return Result containing the loaded map or error information
 */
Result map_load_from_csv(const char *file_path);

/**
 * @brief Frees resources held by a map object
 *
 * @param map map to free
 */
void map_destroy(Map *map);

/**
 * @brief Renders the map to the screen
 *
 * @param map Pointer to the map to render
 */
void map_draw(Map *map);
