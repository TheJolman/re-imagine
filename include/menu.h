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
    void (*select)(const void *);
    size_t selectedItem;
    size_t numItems;
    MenuItem *items[];
} GridMenu;

typedef struct
{
    void (*nextItem)(const void *);
    void (*prevItem)(const void *);
    void (*select)(const void *);
    size_t selectedItem;
    size_t numItems;
    MenuItem items[];
} VerticalMenu;

GridMenu *gridMenuCreate(size_t numItems);
VerticalMenu *verticalMenuCreate(size_t numItems);
