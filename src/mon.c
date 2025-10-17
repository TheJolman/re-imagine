#include "mon.h"
#include "debug.h"
#include "raylib.h"
#include "utils.h"
#include <cjson/cJSON.h>
#include <stdio.h>
#include <string.h>

void load_mon_texture(Mon *mon, MonSpriteView textureType)
{
    char imagePath[256];
    if (!mon->name)
    {
        error_exit(1, "attempted to load texture of mon with no name");
    }
    snprintf(imagePath, sizeof(imagePath), "assets/%s/sprite.png", mon->name);

    switch (textureType)
    {
    case FRONT:
        break;
    case BACK:
        break;
    }

    if (mon->sprite.texture.id > 0)
    {
        UnloadTexture(mon->sprite.texture);
    }

    Image image = LoadImage(imagePath);
    mon->sprite.texture = LoadTextureFromImage(image);
    UnloadImage(image);

    mon->sprite_view = textureType;
}

Result create_mon(char *name, unsigned level)
{
    Mon *mon = heap_list.malloc(sizeof(Mon));
    if (!mon)
    {
        return (Result){.value = nullptr, .err = "Out of memory"};
    }

    mon->name = heap_list.malloc(strlen(name) + 1);
    if (!mon->name)
    {
        heap_list.free(mon);
        return (Result){.value = nullptr, .err = "Out of memory"};
    }
    strcpy((char *)mon->name, name);

    mon->sprite = (Sprite){
        .texture = {0},
        .rotation = 0.0f,
        .scale = 1.0f,
        .tint = WHITE,
    };
    mon->health = (Health){100, 100};
    mon->level = level;
    // TODO: Initialize other values

    return (Result){.value = mon, .err = nullptr};
}

void destroy_mon(Mon *mon)
{
    if (mon->sprite.texture.id > 0)
    {
        UnloadTexture(mon->sprite.texture);
    }
    heap_list.free((char *)mon->name);
    heap_list.free(mon);
    mon = nullptr;
}
