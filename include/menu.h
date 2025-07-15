#pragma once

#include "raylib.h"
#include <stdlib.h>


typedef struct
{
    char *text;
    int posX;
    int posY;
    int fontSize;
    Color color;
} MenuItem;

typedef struct
{
    void (*moveLeft)(const void *);
    void (*moveRight)(const void *);
    void (*moveDown)(const void *);
    void (*moveUp)(const void *);
    size_t selected_item;
    size_t numItems;
    MenuItem *items[];
} GridMenu;

typedef struct
{
    void (*nextItem)(const void *);
    void (*prevItem)(const void *);
    size_t selected_item;
    size_t numItems;
    MenuItem items[];
} VeticalMenu;

GridMenu *createGridMenu();
GridMenu *createVerticalMenu();


