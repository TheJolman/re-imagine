#pragma once

#include "map.h"
#include "player.h"
#include "raylib.h"
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Updates player collision box based on their current position
 * @param player Pointer to player
 */
void update_player_collision_box(Player *player);

/**
 * @brief Gets the tile value at the specified coordinates in the map
 *
 * @param map Pointer to map
 * @param x x coordinate in tile unite
 * @param y y coordinate in tile units
 * @return The tile value
 */
int16_t get_tile_value(Map *map, uint32_t x, uint32_t y);

/**
 * @brief Checks if a tile at the given coordinates is a boundary tile
 *
 * @return true if the tile is a boundary
 */
bool is_boundary(Map *map, uint32_t x, uint32_t y);

/**
 * @brief Checks if a collision box collides with any boundary tiles in the map
 *
 * @param collision_box Rectangle collision box
 * @return true if collision is detected else false
 */
bool check_map_collision(Map *map, Rectangle collision_box);

/**
 * @brief Resolves collision
 *
 * @param prev_position The player's previous position before collision
 */
void resolve_map_collsion(Map *map, Player *player, Vector2 prev_position);