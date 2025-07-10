#include "mon.h"
#include <string.h>

static void loadMonTextures(Mon *mon)
{
    // NOTE: We could specialize this for players and enemies since players only see the back
    // and enemies only see the front.
    char frontTexturePath[256];
    auto basePath = "assets/";
    strcpy(frontTexturePath, basePath);
    strcpy(frontTexturePath, mon->name);
    strcat(frontTexturePath, "-front.png");
    Image image = LoadImage(frontTexturePath);
    mon->textures.frontTexture = LoadTextureFromImage(image);

    char backTexturePath[256];
    strcpy(backTexturePath, basePath);
    strcpy(frontTexturePath, mon->name);
    strcat(backTexturePath, "-back.png");
    image = LoadImage(backTexturePath);
    mon->textures.backTexture = LoadTextureFromImage(image);

    // Don't really have a use for these
    mon->textures.scale = 0.0f;
    mon->textures.tint = WHITE;
}

Mon createMon(char *name)
{
    Mon mon = {0};
    loadMonTextures(&mon);

    // TODO: Initialize other values

    return mon;
}
