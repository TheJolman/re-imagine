#pragma once

#include "raylib.h"
#include "stdint.h"

typedef struct {
    Texture2D texture;
    Rectangle source;
    float rotation;
    float scale;
    Color tint;
} Sprite;

typedef uint32_t HitPoints;

typedef struct {
    HitPoints current, max;
} Health;

typedef struct SpriteAnimation {
    Texture2D atlas;               ///< Sprite sheet texture
    Texture2D current_frame;       ///< Currently displayed frame
    int frames_per_second;         ///< Animation speed (1-6 FPS)
    float time_started;            ///< Timestamp for frame timing
    const Rectangle *rectangles;   ///< Array of frame source rects (points to static data)
    int rectangles_length;         ///< Num frames
} SpriteAnimation;

/**
 * Container for various player animations
 */
typedef struct {
    SpriteAnimation right, left, up, down, idle;
    SpriteAnimation *current;
} PlayerAnimations;
