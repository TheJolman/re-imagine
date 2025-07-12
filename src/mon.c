#include "mon.h"
#include "debug.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void loadMonTextures(Mon *mon)
{
    // NOTE: We could specialize this for players and enemies since players only see the back
    // and enemies only see the front.
    char frontTexturePath[256];
    auto basePath = "assets/";
    strcpy(frontTexturePath, basePath);
    if (!mon->name) {
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

    // Don't really have a use for these
    mon->textures.scale = 0.0f;
    mon->textures.tint = WHITE;
}

Mon createMon(char *name)
{
    Mon mon = {name = name};
    loadMonTextures(&mon);

    // TODO: Initialize other values

    return mon;
}
