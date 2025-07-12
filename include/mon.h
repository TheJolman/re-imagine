#pragma once

#include "raylib.h"

typedef struct
{
    Texture2D frontTexture;
    Texture2D backTexture;
} MonTextures;

typedef struct
{
    const char *name;
    const unsigned damage;
} Move;

typedef struct
{
    const char *name;
    MonTextures textures;
    Move moves[4];
    unsigned hp;
} Mon;

Mon *createMon(char *name);
void loadMonTextures(Mon *mon);
