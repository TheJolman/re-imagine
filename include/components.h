#pragma once

#include "raylib.h"
#include "stdint.h"

typedef struct
{
    Vector2 vec;
    float max_speed;
} Velocity;

typedef Vector2 Position;

typedef struct
{
    Texture2D texture;
    float rotation;
    float scale;
    Color tint;
} Sprite;

typedef uint32_t HitPoints;

typedef struct
{
    HitPoints current, max;
} Health;

typedef struct SpriteAnimation
{
    Texture2D atlas;
    Texture2D currentFrame;
    int framesPerSecond;
    float timeStarted;

    Rectangle *rectangles;
    int rectanglesLength;
} SpriteAnimation;

/**
 * Container for various player animations
 */
typedef struct
{
    SpriteAnimation right;
    SpriteAnimation left;
    SpriteAnimation up;
    SpriteAnimation down;
    SpriteAnimation idle;
    SpriteAnimation *current;
} PlayerAnimations;
