#pragma once

#include "raylib.h"
typedef struct
{
    Vector2 vec;
    float max_speed;
} Velocity;

typedef Vector2 Position;

typedef struct
{
    Texture2D asset;
    Position pos;
    float rotation;
    float scale;
    Color tint;
} Sprite;
