#include "mon.h"
#include <string.h>

static void loadMonTextures(Mon *mon)
{
    // NOTE: We could specialize this for players and enemies since players only see the back
    // and enemies only see the front.
    auto basePath = "assets/";
    auto baseName = strcpy("", mon->name);

    const char *frontTextureFileName = strcat(baseName, "-front.png");
    const char *backTextureFileName = strcat(baseName, "-back.png");

    auto frontTexturePath = strcat(basePath, frontTextureFileName);
    auto backTexturePath = strcat(basePath, backTextureFileName);

    Image image = LoadImage(frontTexturePath);
    mon->textures.frontTexture = LoadTextureFromImage(image);

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
