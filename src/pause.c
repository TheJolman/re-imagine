#include "pause.h"
#include "assert.h"
#include "menu.h"
#include "raylib.h"
#include <string.h>

constexpr size_t NUM_ITEMS = 3;

static void optionsSelect(void) { return; }
static void exitSelect(void)
{
    pauseMenuEnd();
    CloseWindow();
}
static void creditsSelect(void) { return; }

// NOTE: maybe move these into the create function?

// clang-format off
static const MenuItem optionsItem = {"OPTIONS", 50, 100, 20, DARKGRAY, optionsSelect};
static const MenuItem exitItem =    {"EXIT",    50, 130, 20, DARKGRAY, exitSelect};
static const MenuItem creditsItem = {"CREDITS", 50, 160, 20, DARKGRAY, creditsSelect};
// clang-format on

static const MenuItem pauseItems[NUM_ITEMS] = {optionsItem, exitItem, creditsItem};

VerticalMenu *pauseMenu = nullptr;

static VerticalMenu *pauseMenuCreate()
{
    VerticalMenu *menu = verticalMenuCreate(NUM_ITEMS);
    if (menu)
    {
        for (size_t i = 0; i < menu->numItems; i++)
            menu->items[i] = pauseItems[i];
    }

    return menu;
}

void pauseMenuDisplay(void)
{
    if (!pauseMenu)
    {
        pauseMenu = pauseMenuCreate();
        if (!pauseMenu)
            return;
    }

    DrawText("PAUSE MENU", 50, 50, 40, DARKGRAY);

    for (int i = 0; i < pauseMenu->numItems; i++)
    {
        MenuItem item = pauseItems[i];
        DrawText(item.text, item.posX, item.posY, item.fontSize, item.color);
    }

    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
    {
        assert(pauseMenu->nextItem);
        pauseMenu->nextItem(pauseMenu);
    }
    else if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
    {
        assert(pauseMenu->prevItem);
        pauseMenu->prevItem(pauseMenu);
    }
    else if (IsKeyPressed(KEY_ENTER))
        pauseMenu->items[pauseMenu->selectedItem].select();

    MenuItem currentItem = pauseItems[pauseMenu->selectedItem];
    DrawRectangleLines(currentItem.posX - 10, currentItem.posY - 5, 300, 30, DARKGRAY);
}

void pauseMenuEnd()
{
    if (pauseMenu)
        verticalMenuDestroy(pauseMenu);

    pauseMenu = nullptr;
}
