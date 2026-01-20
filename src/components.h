#pragma once

#include "raylib.h"
#include "stdint.h"

typedef struct {
    Vector2 vec;
    float max_speed;
} Velocity;

typedef Vector2 Position;

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
    Texture2D atlas;
    Texture2D current_frame;
    int frames_per_second;
    float time_started;

    Rectangle *rectangles;
    int rectangles_length;
} SpriteAnimation;

/**
 * Container for various player animations
 */
typedef struct {
    SpriteAnimation right;
    SpriteAnimation left;
    SpriteAnimation up;
    SpriteAnimation down;
    SpriteAnimation idle;
    SpriteAnimation *current;
} PlayerAnimations;
