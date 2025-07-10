#include "mon.h"
#include "debug.h"
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
    debug_log("Loading asset: %s", frontTexturePath);
    Image image = LoadImage(frontTexturePath);
    UnloadImage(image);
    mon->textures.frontTexture = LoadTextureFromImage(image);

    char backTexturePath[256];
    strcpy(backTexturePath, basePath);
    strcpy(backTexturePath, mon->name);
    strcat(backTexturePath, "-back.png");
    debug_log("Loading asset: %s", backTexturePath);
    image = LoadImage(backTexturePath);
    UnloadImage(image);
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
