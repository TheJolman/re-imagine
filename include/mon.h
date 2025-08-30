#pragma once

#include "raylib.h"
#include "utils.h"

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

Result create_mon(char *name);
void destroy_mon(Mon *mon);
void load_mon_texture(Mon *mon, MonTextureType);
