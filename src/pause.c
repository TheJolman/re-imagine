#include "pause.h"
#include "assert.h"
#include "menu.h"
#include "raylib.h"

constexpr size_t NUM_ITEMS = 3;

// typedef struct
// {
//     char *name;
//     int posX;
//     int posY;
//     int fontSize;
//     Color color;
// } PauseItem;

typedef enum
{
    OPTIONS,
    EXIT,
    CREDITS
} MenuIndices;

static void optionsSelect(void) { return; }
static void exitSelect(void) { return; }
static void creditsSelect(void) { return; }

// clang-format off
static const MenuItem optionsItem = {"OPTIONS", 50, 100, 20, DARKGRAY, optionsSelect};
static const MenuItem exitItem =    {"EXIT",    50, 130, 20, DARKGRAY, exitSelect};
static const MenuItem creditsItem = {"CREDITS", 50, 160, 20, DARKGRAY, creditsSelect};
// clang-format on

static const MenuItem pauseItems[NUM_ITEMS] = {optionsItem, exitItem, creditsItem};

VerticalMenu *menu = nullptr;

void pauseMenuNext(int *currentPos)
{
    // wraps to top
    if (*currentPos == NUM_ITEMS - 1)
    {
        *currentPos = 0;
    }
    else
    {
        *currentPos += 1;
    }
}

void pauseMenuPrev(int *currentPos)
{
    // wraps to bottom
    if (*currentPos == 0)
    {
        *currentPos = NUM_ITEMS - 1;
    }
    else
    {
        *currentPos -= 1;
    }
}

void pauseMenuDisplay(void)
{
    if (!menu)
    {
        menu = verticalMenuCreate(NUM_ITEMS);
    }
    DrawText("PAUSE MENU", 50, 50, 40, DARKGRAY);

    for (int i = 0; i < NUM_ITEMS; ++i)
    {
        // TODO: Use consistenet styling for all and make PauseItem less complex (maybe)
        MenuItem item = pauseItems[i];
        DrawText(item.text, item.posX, item.posY, item.fontSize, item.color);
    }

    assert(currentMenuIndex >= 0 && currentMenuIndex < NUM_ITEMS);
    MenuItem currentItem = pauseItems[currentMenuIndex];
    DrawRectangleLines(currentItem.posX - 10, currentItem.posY - 5, 300, 30, DARKGRAY);
}

void pauseMenuSelect(void)
{
    assert(currentMenuIndex >= 0 && currentMenuIndex < NUM_ITEMS);

    switch (currentMenuIndex)
    {
    case OPTIONS:
        // TODO: Implement options menu
        break;
    case EXIT:
        CloseWindow();
        break;
    case CREDITS:
        // TODO: Implement credits
        break;
    }
}
