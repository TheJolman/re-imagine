#include "mon.h"
#include "debug.h"
#include "raylib.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void loadOneTexture(char *imagePath, Texture2D *texture)
{
    Image image = LoadImage(imagePath);
    *texture = LoadTextureFromImage(image);
    UnloadImage(image);
}

void loadMonTexture(Mon *mon, MonTextureType textureType)
{
    char imagePath[256];
    Image image = {};
    if (!mon->name)
    {
        fputs("ERROR: Can not load texture of mon with no name", stderr);
        exit(1);
    }

    switch (textureType)
    {
    case FRONT:
        snprintf(imagePath, sizeof(imagePath), "assets/%s-front.png", mon->name);
        break;
    case BACK:
        snprintf(imagePath, sizeof(imagePath), "assets/%s-back.png", mon->name);
        break;
    }

    image = LoadImage(imagePath);
    *mon->texture = LoadTextureFromImage(image);
    UnloadImage(image);
}

Result createMon(char *name)
{
    Mon *mon = malloc(sizeof(Mon));
    if (!mon)
    {
        return (Result){.value = nullptr, .err = "Out of memory "};
    }

    mon->name = malloc(strlen(name) + 1);
    if (!mon->name)
    {
        return (Result){.value = nullptr, .err = "Out of memory "};
    }
    strcpy((char *)mon->name, name);
    mon->texture = malloc(sizeof(Texture2D));
    if (!mon->texture)
    {
        return (Result){.value = nullptr, .err = "Out of memory "};
    }
    mon->hp = 100;
    // TODO: Initialize other values

    return (Result){.value = mon, .err = nullptr};
}

void destroyMon(Mon *mon)
{
    if (mon)
    {
        if (mon->texture)
        {
            UnloadTexture(*mon->texture);
            free(mon->texture);
        }
        if (mon->name)
        {
            free((char *)mon->name);
        }
        free(mon);
    }
}
