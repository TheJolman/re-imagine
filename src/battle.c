#include "battle.h"
#include "map.h"
#include "mon.h"
#include "raylib.h"

const int windowMargin = 50;
const int textHeight = 150;

Mon playerMon = {0};
Mon enemyMon = {0};

// extern Image frogeFrontImage;
// extern Texture2D frogeFrontTexture;
// const float frogeScale = 0.4f;

void BattleScene(void)
{
    DrawText("Battle scene is active!\nPress B to go back!", 50, 50, 20, DARKGRAY);

    const Vector2 enemyPosition = {40, 40};
    const Vector2 playerPosition = {screen.width - 500, screen.height - 500};

    // TODO:: get rid of magic numbers

    if (!IsTextureValid(playerMon.textures.backTexture))
        loadMonTextures(&playerMon);

    //  Draw text box
    DrawRectangleLines(windowMargin, screen.height - (windowMargin + textHeight),
                       screen.width - windowMargin * 2, textHeight, BLACK);

    // Render art for enemy mon
    DrawTextureEx(playerMon.textures.frontTexture, enemyPosition, 0.0f, playerMon.textures.scale,
                  playerMon.textures.tint);
    // Draw hp bar for enemy mon

    // Render art for players mon
    DrawTextureEx(playerMon.textures.backTexture, playerPosition, 0.0f, playerMon.textures.scale,
                  playerMon.textures.tint);
    // Draw hp bar for players mon

    // Draw experience bar for players mon
}
