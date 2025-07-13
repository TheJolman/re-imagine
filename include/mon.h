#pragma once

#include "raylib.h"

typedef enum
{
    FRONT,
    BACK
} MonTextureType;

typedef struct
{
    const char *name;
    const unsigned damage;
} Move;

typedef struct
{
    const char *name;
    Texture2D *texture;
    MonTextureType textureType;
    Move moves[4];
    unsigned hp;
} Mon;

Mon *createMon(char *name);
void destroyMon(Mon *mon);
void loadMonTexture(Mon *mon, MonTextureType);
