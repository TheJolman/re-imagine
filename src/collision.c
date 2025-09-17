#include "raylib.h"
#include <stdint.h>
#include <collision.h>
#include <player.h>
#include <map.h>


void update_player_collision_box(Player *player) {
    player->collision_box = (Rectangle) {
    player->position.x - player->size / 2,
    player->position.y - player->size / 2,
    player->size,
    player->size
    };
}

int16_t get_tile_value(Map *map, uint32_t x, uint32_t y) {
    if (x >= map->width || y >= map->height) { 
        return 3; 
    }

    return map->data[y * map->width + x]; // 2D point to 1D array 
}

bool is_boundary(Map *map, uint32_t x, uint32_t y) {
    return get_tile_value(map, x, y) == 3;
}

bool check_map_collision(Map *map, Rectangle collision_box) {
    // Tile coordinates that collision_box overlaps with
    uint32_t left_tile = (uint32_t)(collision_box.x / MAP_TILE_SIZE);
    uint32_t right_tile = (uint32_t)(collision_box.x + collision_box.width - 1 / MAP_TILE_SIZE);
    uint32_t top_tile = (uint32_t)(collision_box.y / MAP_TILE_SIZE);
    uint32_t bottom_tile = (uint32_t)(collision_box.y + collision_box.height - 1 / MAP_TILE_SIZE);

    for (uint32_t x = left_tile; x <= right_tile; ++x) {
        for (uint32_t y = top_tile; y <= bottom_tile; ++y) {
            if (is_boundary(map, x, y)) {
                return true;
            }
        }
    }

    return false;
}


void resolve_map_collsion(Map *map, Player *player, Vector2 prev_position){
    // TODO: Implement collision handling 
}


