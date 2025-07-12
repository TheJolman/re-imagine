#include "mon.h"
#include "debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void loadMonTextures(Mon *mon)
{
    // NOTE: We don't need to load both images at once
    char frontTexturePath[256];
    auto basePath = "assets/";
    strcpy(frontTexturePath, basePath);
    if (!mon->name)
    {
        fprintf(stderr, "ERROR: Can not load texture of mon with no name");
        exit(1);
    }
    strcat(frontTexturePath, mon->name);
    strcat(frontTexturePath, "-front.png");
    debug_log("Loading asset: %s", frontTexturePath);
    printf("Loading asset: %s", frontTexturePath);
    Image image = LoadImage(frontTexturePath);
    mon->textures.frontTexture = LoadTextureFromImage(image);
    UnloadImage(image);

    char backTexturePath[256];
    strcpy(backTexturePath, basePath);
    strcat(backTexturePath, mon->name);
    strcat(backTexturePath, "-back.png");
    debug_log("Loading asset: %s", backTexturePath);
    image = LoadImage(backTexturePath);
    mon->textures.backTexture = LoadTextureFromImage(image);
    UnloadImage(image);
}

Mon *createMon(char *name)
{
    Mon *mon = malloc(sizeof(Mon));
    mon->name = name;
    // TODO: Initialize other values
    return mon;
}
