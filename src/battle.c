#include "battle.h"
#include "map.h"
#include "menu.h"
#include "mon.h"
#include "raylib.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

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

static MenuItem attackItem = {"ATTACK", 0, 0, 20, DARKGRAY, attackSelect};
static MenuItem itemsItem =  {"ITEMS",  0, 0, 20, DARKGRAY, itemsSelect};
static MenuItem runItem =    {"RUN",    0, 0, 20, DARKGRAY, runSelect};
static MenuItem switchItem = {"SWITCH", 0, 0, 20, DARKGRAY, switchSelect};
// clang-format on

Mon *playerMon = nullptr;
Mon *enemyMon = nullptr;
BattleUI ui = {0};
static bool battleInitialized = false;

static MenuItem actionItems[NUM_ROWS][NUM_COLS];

static void updateMenuItemPositions()
{
    float menuStartX = ui.textBox.x + ui.textBox.width * 0.5f + 10;
    float menuStartY = ui.textBox.y + 30;
    float itemSpacing = 35;

    attackItem.posX = menuStartX;
    attackItem.posY = menuStartY;

    itemsItem.posX = menuStartX + 120;
    itemsItem.posY = menuStartY;

    runItem.posX = menuStartX;
    runItem.posY = menuStartY + itemSpacing;

    switchItem.posX = menuStartX + 120;
    switchItem.posY = menuStartY + itemSpacing;

    actionItems[0][0] = attackItem;
    actionItems[0][1] = itemsItem;
    actionItems[1][0] = runItem;
    actionItems[1][1] = switchItem;
}

GridMenu *actionMenu = nullptr;
GridMenu *attackMenu = nullptr;
GridMenu *itemsMenu = nullptr;
GridMenu *switchMenu = nullptr;

static GridMenu *actionMenuCreate()
{
    GridMenu *menu = gridMenuCreate(NUM_ITEMS, NUM_ROWS, NUM_COLS);
    if (!menu)
    {
        return nullptr;
    }

    for (size_t row = 0; row < NUM_ROWS; row++)
    {
        for (size_t col = 0; col < NUM_COLS; col++)
        {
            size_t index = row * NUM_COLS + col;
            if (index >= menu->numItems)
            {
                gridMenuDestroy(menu);
                return nullptr;
            }
            menu->items[index] = &actionItems[row][col];
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
    {
        actionMenu = actionMenuCreate();
        if (!actionMenu)
            return;
    }

    float menuTitleX = ui.textBox.x + ui.textBox.width * 0.5f + 10;
    float menuTitleY = ui.textBox.y + 5;
    DrawText("BATTLE MENU", menuTitleX, menuTitleY, 18, WHITE);

    DrawLine(ui.textBox.x + ui.textBox.width * 0.5f, ui.textBox.y,
             ui.textBox.x + ui.textBox.width * 0.5f, ui.textBox.y + ui.textBox.height, GRAY);
    for (size_t i = 0; i < actionMenu->grid.numRows; i++)
    {
        for (size_t j = 0; j < actionMenu->grid.numCols; j++)
        {
            MenuItem item = actionItems[i][j];
            if (item.text)
            {
                DrawText(item.text, item.posX, item.posY, item.fontSize, item.color);
            }
        }
    }

    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
    {
        if (actionMenu->moveDown)
            actionMenu->moveDown(actionMenu);
    }
    else if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
    {
        if (actionMenu->moveUp)
            actionMenu->moveUp(actionMenu);
    }
    else if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
    {
        if (actionMenu->moveLeft)
            actionMenu->moveLeft(actionMenu);
    }
    else if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
    {
        if (actionMenu->moveRight)
            actionMenu->moveRight(actionMenu);
    }
    else if (IsKeyPressed(KEY_ENTER))
    {
        if (actionMenu->grid.currentRow < actionMenu->grid.numRows &&
            actionMenu->grid.currentCol < actionMenu->grid.numCols)
        {
            size_t index = actionMenu->grid.currentRow * actionMenu->grid.numCols +
                           actionMenu->grid.currentCol;
            if (index < actionMenu->numItems && actionMenu->items[index]->select)
            {
                actionMenu->items[index]->select();
                actionMenuEnd();
            }
        }
    }

    if (actionMenu->grid.currentRow < NUM_ROWS && actionMenu->grid.currentCol < NUM_COLS)
    {
        MenuItem currentItem =
            actionItems[actionMenu->grid.currentRow][actionMenu->grid.currentCol];
        DrawRectangleLines(currentItem.posX - 10, currentItem.posY - 5, 300, 30, DARKGRAY);
    }
}

static void initBattleUI(void)
{
    ui.textBox = (Rectangle){windowMargin, screen.height - (windowMargin + textHeight),
                             screen.width - windowMargin * 2, textHeight};

    // TODO: Get consistent asset sizes
    ui.playerMonPos = (Vector2){screen.width * 0.6f, screen.height * 0.35f};
    ui.enemyMonPos = (Vector2){screen.width * 0.05f, screen.height * 0.1f};
    ui.actionMenuPos = (Vector2){ui.textBox.x + 20, ui.textBox.y + 20};
    ui.statusBarPos = (Vector2){ui.textBox.x + 20, ui.textBox.y + 80};

    updateMenuItemPositions();
    battleState = BATTLE_MENU;

    if (!playerMon)
    {
        playerMon = createMon("froge");
        if (playerMon)
        {
            playerMon->hp = 100;
            loadMonTexture(playerMon, BACK);
        }
    }

    if (!enemyMon)
    {
        enemyMon = createMon("froge");
        if (enemyMon)
        {
            enemyMon->hp = 80;
            loadMonTexture(enemyMon, FRONT);
        }
    }
}

static void renderMon(Mon *mon, Vector2 position)
{
    if (!mon)
        return;

    if (!mon->texture)
        return;

    if (!IsTextureValid(*mon->texture))
        return;

    DrawTextureEx(*mon->texture, position, ROTATION, SCALE, TINT);
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

    if (playerMon)
        renderMon(playerMon, ui.playerMonPos);

    if (enemyMon)
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
    if (playerMon)
    {
        destroyMon(playerMon);
        playerMon = nullptr;
    }

    if (enemyMon)
    {
        destroyMon(enemyMon);
        enemyMon = nullptr;
    }

    actionMenuEnd();
    battleState = BATTLE_MENU;
    battleInitialized = false;
}
