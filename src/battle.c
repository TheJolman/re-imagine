#include "battle.h"
#include "map.h"
#include "menu.h"
#include "mon.h"
#include "raylib.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

// Should these be moved into initBattleUI ?
constexpr int windowMargin = 50;
constexpr int textHeight = 150;
constexpr Color TINT = WHITE;
constexpr float ROTATION = 0.0;
constexpr float SCALE = 0.6f;
constexpr size_t NUM_ITEMS = 4;
constexpr size_t NUM_ROWS = 2;
constexpr size_t NUM_COLS = 2;

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
    BATTLE_RUN,
    BATTLE_SWITCH,
} BattleState;

static BattleState battleState = BATTLE_MENU;

// clang-format off
static void attackSelect() { battleState = BATTLE_ATTACK; }
static void itemsSelect()  { battleState = BATTLE_ITEMS; }
static void runSelect()    { battleState = BATTLE_RUN; }
static void switchSelect() { battleState = BATTLE_SWITCH; }

static const MenuItem attackItem = {"ATTACK", 50, 100, 20, DARKGRAY, attackSelect};
static const MenuItem itemsItem =  {"ITEMS",  50, 130, 20, DARKGRAY, itemsSelect};
static const MenuItem runItem =    {"RUN",    50, 160, 20, DARKGRAY, runSelect};
static const MenuItem switchItem = {"SWITCH", 50, 160, 20, DARKGRAY, switchSelect};
// clang-format on

static const MenuItem actionItems[NUM_ROWS][NUM_COLS] = {{attackItem, itemsItem},
                                                         {runItem, switchItem}};

GridMenu *actionMenu = nullptr;
GridMenu *attackMenu = nullptr;
GridMenu *itemsMenu = nullptr;
GridMenu *switchMenu = nullptr;

static GridMenu *actionMenuCreate()
{
    GridMenu *menu = gridMenuCreate(NUM_ITEMS, NUM_ROWS, NUM_COLS);
    if (menu)
    {
        for (size_t row = 0; row < NUM_ROWS; row++)
        {
            for (size_t col = 0; col < NUM_COLS; col++)
            {
                size_t index = row * NUM_COLS + col;
                puts("Before memcpy");
                memcpy(&menu->items[index], &actionItems[row][col], sizeof(MenuItem));
                puts("After memcpy");
            }
        }
    }
    return menu;
}

static void actionMenuEnd()
{
    if (actionMenu)
        gridMenuDestroy(actionMenu);

    actionMenu = nullptr;
}

static void actionMenuDisplay()
{
    if (!actionMenu)
        actionMenu = actionMenuCreate();

    DrawText("BATTLE MENU", screen.width * 0.6f, screen.height * 0.35f, 20, WHITE);
    for (size_t i = 0; i < actionMenu->grid.numRows; i++)
    {
        for (size_t j = 0; j < actionMenu->grid.numCols; j++)
        {
            MenuItem item = actionItems[i][j];
            DrawText(item.text, item.posX, item.posY, item.fontSize, item.color);
        }
    }

    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
    {
        assert(actionMenu->moveDown);
        actionMenu->moveDown(actionMenu);
    }
    else if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
    {
        assert(actionMenu->moveUp);
        actionMenu->moveUp(actionMenu);
    }
    else if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
    {
        assert(actionMenu->moveLeft);
        actionMenu->moveLeft(actionMenu);
    }
    else if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
    {
        assert(actionMenu->moveRight);
        actionMenu->moveRight(actionMenu);
    }
    else if (IsKeyPressed(KEY_ENTER))
    {
        actionMenu->items[actionMenu->grid.currentRow][actionMenu->grid.currentCol].select();
        actionMenuEnd();
    }

    MenuItem currentItem = actionItems[actionMenu->grid.currentRow][actionMenu->grid.currentCol];
    DrawRectangleLines(currentItem.posX - 10, currentItem.posY - 5, 300, 30, DARKGRAY);
}

Mon *playerMon = nullptr;
Mon *enemyMon = nullptr;
BattleUI ui = {0};
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
        actionMenuDisplay();
        break;
    case BATTLE_ATTACK:
        // attackMenuDisplay();
        break;
    case BATTLE_ITEMS:
        // itemsMenuDisplay();
        break;
    case BATTLE_RUN:
        // runMenuDisplay();
        break;
    case BATTLE_SWITCH:
        // switchMenuDisplay();
        break;
    }
}

static void renderBattleUI(void)
{
    renderTextBox();
    renderActionMenu();
    renderMon(playerMon, ui.playerMonPos);
    renderMon(enemyMon, ui.enemyMonPos);
}

void BattleScene(void)
{
    if (!battleInitialized)
    {
        initBattleUI();
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
