#include "battle.h"
#include "map.h"
#include "mon.h"
#include "raylib.h"
#include <stdlib.h>

constexpr int windowMargin = 50;
constexpr int textHeight = 150;
constexpr Color TINT = WHITE;
constexpr float ROTATION = 0.0;
constexpr float SCALE = 0.6f;

Mon *playerMon = nullptr;
Mon *enemyMon = nullptr;

void renderPlayerMon(Mon *mon)
{
    const Vector2 playerPosition = {screen.width - 500, screen.height - 500};
    DrawTextureEx(*playerMon->texture, playerPosition, ROTATION, SCALE, TINT);
}

void renderEnemyMon(Mon *mon)
{
    const Vector2 enemyPosition = {40, 40};
    DrawTextureEx(*enemyMon->texture, enemyPosition, ROTATION, SCALE, TINT);
}

void renderUI()
{
    DrawRectangleLines(windowMargin, screen.height - (windowMargin + textHeight),
                       screen.width - windowMargin * 2, textHeight, WHITE);

    renderEnemyMon(enemyMon);
    renderPlayerMon(playerMon);
}

void BattleScene(void)
{
    DrawText("Battle scene is active!\nPress B to go back!", 50, 50, 20, DARKGRAY);

    // Hardcode only asset for now
    if (!playerMon)
        playerMon = createMon("froge");
    if (!IsTextureValid(*playerMon->texture))
        loadMonTexture(playerMon, BACK);

    if (!enemyMon)
        enemyMon = createMon("froge");
    if (!IsTextureValid(*enemyMon->texture))
        loadMonTexture(enemyMon, FRONT);

    renderUI();
}

void EndBattleScene(void)
{
    destroyMon(playerMon);
    destroyMon(enemyMon);
    playerMon = nullptr;
    enemyMon = nullptr;
}
