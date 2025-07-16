#include "menu.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// TODO: do some extra math so empty squares can't get hovered
static void gridMenuLeft(const void *menuPtr)
{
    GridMenu *menu = (GridMenu *)menuPtr;
    if (menu->grid.currentCol > 0)
        menu->grid.currentCol--;
    else
        menu->grid.currentCol = menu->grid.numCols - 1;
}

static void gridMenuRight(const void *menuPtr)
{
    GridMenu *menu = (GridMenu *)menuPtr;
    if (menu->grid.currentCol < menu->grid.numCols - 1)
        menu->grid.currentCol++;
    else
        menu->grid.currentCol = 0;
}

static void gridMenuUp(const void *menuPtr)
{
    GridMenu *menu = (GridMenu *)menuPtr;
    if (menu->grid.currentRow > 0)
        menu->grid.currentRow--;
    else
        menu->grid.currentRow = menu->grid.numRows - 1;
}

static void gridMenuDown(const void *menuPtr)
{
    GridMenu *menu = (GridMenu *)menuPtr;
    if (menu->grid.currentRow < menu->grid.numRows - 1)
        menu->grid.currentRow++;
    else
        menu->grid.currentRow = 0;
}

GridMenu *gridMenuCreate(size_t numItems)
{
    GridMenu *menu = malloc(sizeof(GridMenu) + numItems * sizeof(MenuItem *));
    if (!menu)
        return nullptr;

    menu->numItems = numItems;
    menu->moveLeft = gridMenuLeft;
    menu->moveRight = gridMenuRight;
    menu->moveDown = gridMenuDown;
    menu->moveUp = gridMenuUp;

    memset(menu, 0, numItems * sizeof(MenuItem *));
    return menu;
}

void gridMenuDestroy(GridMenu *menu)
{
    if (menu)
        free(menu);
}

static void verticalMenuNext(const void *menuPtr)
{
    VerticalMenu *menu = (VerticalMenu *)menuPtr;

    if (menu->selectedItem < menu->numItems - 1)
        menu->selectedItem++;
    else
        menu->selectedItem = 0;
}

static void verticalMenuPrev(const void *menuPtr)
{
    VerticalMenu *menu = (VerticalMenu *)menuPtr;

    if (menu->selectedItem > 0)
        menu->selectedItem--;
    else
        menu->selectedItem = menu->numItems - 1;
}

VerticalMenu *verticalMenuCreate(const size_t numItems)
{
    VerticalMenu *menu = malloc(sizeof(VerticalMenu) + numItems * sizeof(MenuItem));
    if (!menu)
        return nullptr;

    assert(menu->numItems > 0);

    menu->numItems = numItems;
    menu->nextItem = verticalMenuNext;
    menu->prevItem = verticalMenuPrev;
    menu->selectedItem = 0;
    return menu;
}

void verticalMenuDestroy(VerticalMenu *menu)
{
    if (menu)
        free(menu);
}
