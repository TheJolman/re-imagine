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
    union {
        Texture2D *frontTexture;
        Texture2D *backTexture;
        Texture2D *spriteTexture;
    };
    Move moves[4];
    unsigned hp;
} Mon;

Mon *createMon(char *name);
void loadMonTexture(Mon *mon, MonTextureType);
