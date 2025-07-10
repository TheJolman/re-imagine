#pragma once

#include "raylib.h"

typedef struct
{
    Texture2D frontTexture;
    Texture2D backTexture;
    float scale;
    Color tint;
} MonTextures;

typedef struct
{
    char *name;
    unsigned damage;
} Move;

typedef struct
{
    MonTextures textures;
    Move moves[4];
    unsigned hp;
} Mon;
