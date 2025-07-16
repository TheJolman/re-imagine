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
    void (*select)(void);
} MenuItem;

typedef struct {
    size_t numRows;
    size_t numCols;
    size_t currentRow;
    size_t currentCol;
} Grid;

typedef struct
{
    void (*moveLeft)(const void *);
    void (*moveRight)(const void *);
    void (*moveDown)(const void *);
    void (*moveUp)(const void *);
    Grid grid;
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

GridMenu *gridMenuCreate(const size_t numItems, const size_t numRows, const size_t numCols);
void gridMenuDestroy(GridMenu *menu);

VerticalMenu *verticalMenuCreate(const size_t numItems);
void verticalMenuDestroy(VerticalMenu *menu);
