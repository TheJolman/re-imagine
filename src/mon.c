#include "mon.h"
#include "debug.h"
#include "raylib.h"
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

Mon *createMon(char *name)
{
    Mon *mon = malloc(sizeof(Mon));
    if (!mon)
    {
        debug_log("Error allocating memory");
        exit(1);
    }
    mon->name = malloc(strlen(name) + 1);
    if (!mon->name)
    {
        debug_log("Error allocating memory");
        exit(1);
    }
    strcpy((char *)mon->name, name);
    mon->texture = malloc(sizeof(Texture2D));
    if (!mon->name)
    {
        debug_log("Error allocating memory");
        exit(1);
    }
    mon->hp = 100;
    // TODO: Initialize other values
    return mon;
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
