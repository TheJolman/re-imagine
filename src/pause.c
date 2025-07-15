#include "pause.h"
#include "assert.h"
#include "menu.h"
#include "raylib.h"
#include <string.h>

constexpr size_t NUM_ITEMS = 3;

static void optionsSelect(void) { return; }
static void exitSelect(void) { CloseWindow(); }
static void creditsSelect(void) { return; }

// clang-format off
static const MenuItem optionsItem = {"OPTIONS", 50, 100, 20, DARKGRAY, optionsSelect};
static const MenuItem exitItem =    {"EXIT",    50, 130, 20, DARKGRAY, exitSelect};
static const MenuItem creditsItem = {"CREDITS", 50, 160, 20, DARKGRAY, creditsSelect};
// clang-format on

static const MenuItem pauseItems[NUM_ITEMS] = {optionsItem, exitItem, creditsItem};

VerticalMenu *pauseMenu = nullptr;

static VerticalMenu *pauseMenuCreate()
{
    pauseMenu = verticalMenuCreate(NUM_ITEMS);
    if (pauseMenu)
    {
        for (size_t i = 0; i < pauseMenu->numItems; i++)
            memcpy(&pauseMenu->items[i], &pauseItems[i], sizeof(MenuItem));
    }

    return pauseMenu;
}

void pauseMenuDisplay(void)
{
    if (!pauseMenu)
        pauseMenu = pauseMenuCreate();

    DrawText("PAUSE MENU", 50, 50, 40, DARKGRAY);

    for (int i = 0; i < pauseMenu->numItems; i++)
    {
        MenuItem item = pauseItems[i];
        DrawText(item.text, item.posX, item.posY, item.fontSize, item.color);
    }

    assert(currentMenuIndex >= 0 && currentMenuIndex < NUM_ITEMS);
    MenuItem currentItem = pauseItems[currentMenuIndex];
    DrawRectangleLines(currentItem.posX - 10, currentItem.posY - 5, 300, 30, DARKGRAY);
}
