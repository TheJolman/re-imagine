#include "battle.h"
#include "map.h"
#include "mon.h"
#include "raylib.h"

constexpr int windowMargin = 50;
constexpr int textHeight = 150;
constexpr Color TINT = WHITE;
constexpr float ROTATION = 0.0;
constexpr float SCALE = 0.6f;

typedef struct
{
    Rectangle textBox;
    Vector2 playerMonPos;
    Vector2 enemyMonPos;
    Vector2 actionMenuPos;
    Vector2 statusBarPos;
} BattleUI;

typedef enum
{
    BATTLE_MENU,
    BATTLE_ATTACK,
    BATTLE_ITEMS,
    BATTLE_RUN
} BattleState;

Mon *playerMon = nullptr;
Mon *enemyMon = nullptr;
BattleUI ui = {0};
BattleState battleState = BATTLE_MENU;
static bool battleInitialized = false;

static void initBattleUI(void)
{
    ui.textBox = (Rectangle){windowMargin, screen.height - (windowMargin + textHeight),
                             screen.width - windowMargin * 2, textHeight};

    // TODO: Get consistent asset sizes
    ui.playerMonPos = (Vector2){screen.width * 0.6f, screen.height * 0.35f};

    ui.enemyMonPos = (Vector2){screen.width * 0.05f, screen.height * 0.1f};

    ui.actionMenuPos = (Vector2){ui.textBox.x + 20, ui.textBox.y + 20};

    ui.statusBarPos = (Vector2){ui.textBox.x + 20, ui.textBox.y + 80};
}

static void renderMon(Mon *mon, Vector2 position)
{
    if (mon && mon->texture && IsTextureValid(*mon->texture))
    {
        DrawTextureEx(*mon->texture, position, ROTATION, SCALE, TINT);
    }
}

static void renderTextBox(void)
{
    DrawRectangleLines(ui.textBox.x, ui.textBox.y, ui.textBox.width, ui.textBox.height, WHITE);
}

static void renderActionMenu(void)
{
    switch (battleState)
    {
    case BATTLE_MENU:
        DrawText("FIGHT    BAG", ui.actionMenuPos.x, ui.actionMenuPos.y, 20, WHITE);
        DrawText("SWITCH   RUN", ui.actionMenuPos.x, ui.actionMenuPos.y + 25, 20, WHITE);
        break;
    case BATTLE_ATTACK:
        DrawText("Select an attack:", ui.actionMenuPos.x, ui.actionMenuPos.y, 20, WHITE);
        break;
    case BATTLE_ITEMS:
        DrawText("Select an item:", ui.actionMenuPos.x, ui.actionMenuPos.y, 20, WHITE);
        break;
    case BATTLE_RUN:
        DrawText("Got away safely!", ui.actionMenuPos.x, ui.actionMenuPos.y, 20, WHITE);
        break;
    }
}

static void renderStatusBar(void)
{
    if (playerMon)
    {
        DrawText(TextFormat("%s  HP: %d", playerMon->name, playerMon->hp), ui.statusBarPos.x,
                 ui.statusBarPos.y, 16, WHITE);
    }
    if (enemyMon)
    {
        DrawText(TextFormat("%s  HP: %d", enemyMon->name, enemyMon->hp), ui.statusBarPos.x + 200,
                 ui.statusBarPos.y, 16, WHITE);
    }
}

static void renderBattleUI(void)
{
    renderTextBox();
    renderActionMenu();
    renderStatusBar();
    renderMon(playerMon, ui.playerMonPos);
    renderMon(enemyMon, ui.enemyMonPos);
}

static void initBattleScene(void)
{
    initBattleUI();
    battleState = BATTLE_MENU;

    if (!playerMon)
    {
        playerMon = createMon("froge");
        playerMon->hp = 100;
        loadMonTexture(playerMon, BACK);
    }

    if (!enemyMon)
    {
        enemyMon = createMon("froge");
        enemyMon->hp = 80;
        loadMonTexture(enemyMon, FRONT);
    }
}

void BattleScene(void)
{
    if (!battleInitialized)
    {
        initBattleScene();
        battleInitialized = true;
    }

    DrawText("Battle scene is active!\nPress B to go back!", 50, 50, 20, DARKGRAY);
    renderBattleUI();
}

void EndBattleScene(void)
{
    destroyMon(playerMon);
    destroyMon(enemyMon);
    playerMon = nullptr;
    enemyMon = nullptr;
    battleState = BATTLE_MENU;
    battleInitialized = false;
}
