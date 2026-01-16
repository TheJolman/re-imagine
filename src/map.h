#include <raylib.h>
#include <stdint.h>

/**
 * @brief Map data structure for tile-based rendering
 */
typedef struct {
    uint32_t height;   ///< Map height in tiles
    uint32_t width;    ///< Map width in tiles
    int16_t *data;     ///< 1D array of tile data for simple memory management
    Texture2D tileset; ///< Tileset texture for rendering tiles
} Map;
