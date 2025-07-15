#include "menu.h"
#include <stdlib.h>
#include <string.h>

static void gridMenuLeft(const void *menuPtr)
{
    GridMenu *menu = (GridMenu *)menuPtr;
    if (menu->selectedItem > 0)
    {
    }
}

GridMenu *gridMenuCreate(size_t numItems)
{
    GridMenu *menu = malloc(sizeof(GridMenu) + numItems * sizeof(MenuItem *));
    if (!menu)
        return nullptr;

    menu->numItems = numItems;
    menu->moveLeft = nullptr;
    menu->moveRight = nullptr;
    menu->moveDown = nullptr;
    menu->moveUp = nullptr;

    memset(menu, 0, numItems * sizeof(MenuItem *));
    return menu;
}

static void verticalMenuNext(const void *menuPtr)
{
    VerticalMenu *menu = (VerticalMenu *)menuPtr;

    if (menu->selectedItem > 0)
        menu->selectedItem++;
    else
        menu->selectedItem = 0;
}

static void verticalMenuPrev(const void *menuPtr)
{
    VerticalMenu *menu = (VerticalMenu *)menuPtr;

    if (menu->selectedItem < menu->numItems - 1)
        menu->selectedItem--;
    else
        menu->selectedItem = menu->numItems - 1;
}

VerticalMenu *verticalMenuCreate(size_t numItems)
{
    VerticalMenu *menu = malloc(sizeof(VerticalMenu) + numItems * sizeof(MenuItem));
    if (!menu)
        return nullptr;

    menu->numItems = numItems;
    menu->nextItem = verticalMenuNext;
    menu->prevItem = verticalMenuPrev;
    menu->selectedItem = 0;
    menu->select = nullptr;

    memset(menu, 0, numItems * sizeof(MenuItem *));
    return menu;
}
