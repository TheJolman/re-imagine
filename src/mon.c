#include "mon.h"
// #include "debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static void loadOneTexture(char *imagePath, Texture2D *texture)
{
    Image image = LoadImage(imagePath);
    *texture = LoadTextureFromImage(image);
    UnloadImage(image);
}

void loadMonTexture(Mon *mon, MonTextureType whichTexture)
{
    char imagePath[256];
    Image image = {};
    auto basePath = "assets/";
    strcpy(imagePath, basePath);
    if (!mon->name)
    {
        fprintf(stderr, "ERROR: Can not load texture of mon with no name");
        exit(1);
    }
    strcat(imagePath, mon->name);

    switch (whichTexture)
    {
    case FRONT:
        strcat(imagePath, "-front.png");
        image = LoadImage(imagePath);
        *mon->frontTexture = LoadTextureFromImage(image);
        break;
    case BACK:
        strcat(imagePath, "-back.png");
        image = LoadImage(imagePath);
        *mon->backTexture = LoadTextureFromImage(image);
        break;
    }

    UnloadImage(image);
}

Mon *createMon(char *name)
{
    Mon *mon = malloc(sizeof(Mon));
    mon->name = name;
    mon->name = name;
    // TODO: Initialize other values
    return mon;
}
