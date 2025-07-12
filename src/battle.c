#include "battle.h"
#include "map.h"
#include "mon.h"
#include "raylib.h"

const int windowMargin = 50;
const int textHeight = 150;

Mon *playerMon = nullptr;
Mon *enemyMon = nullptr;

void renderPlayerMon(Mon *mon)
{
    const Vector2 playerPosition = {screen.width - 500, screen.height - 500};
    DrawTextureEx(playerMon->textures.backTexture, playerPosition, 0.0f, playerMon->textures.scale,
                  playerMon->textures.tint);
}

void renderEnemyMon(Mon *mon)
{
    const Vector2 enemyPosition = {40, 40};
    DrawTextureEx(playerMon->textures.frontTexture, enemyPosition, 0.0f, playerMon->textures.scale,
                  playerMon->textures.tint);
}

void BattleScene(void)
{
    DrawText("Battle scene is active!\nPress B to go back!", 50, 50, 20, DARKGRAY);

    // TODO:: get rid of magic numbers

    // Hardcode only asset for now
    if (!playerMon)
        playerMon = createMon("froge");
    if (!IsTextureValid(playerMon->textures.backTexture))
        loadMonTextures(playerMon);

    if (!enemyMon)
        enemyMon = createMon("froge");
    if (!IsTextureValid(enemyMon->textures.backTexture))
        loadMonTextures(enemyMon);

    //  Draw text box
    DrawRectangleLines(windowMargin, screen.height - (windowMargin + textHeight),
                       screen.width - windowMargin * 2, textHeight, BLACK);

    renderEnemyMon(enemyMon);
    renderPlayerMon(playerMon);
    // Draw hp bar for enemy mon

    // Render art for players mon
    // Draw hp bar for players mon

    // Draw experience bar for players mon
}
