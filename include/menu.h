#pragma once

#include "raylib.h"
#include <stdlib.h>


typedef struct
{
    char *text;
    int pos_x;
    int pos_y;
    int font_size;
    Color color;
    void (*select)(void);
} MenuItem;

typedef struct {
    size_t num_rows;
    size_t num_cols;
    size_t current_row;
    size_t current_col;
} Grid;

typedef struct
{
    void (*move_left)(const void *);
    void (*move_right)(const void *);
    void (*move_down)(const void *);
    void (*move_up)(const void *);
    Grid grid;
    size_t num_items;
    MenuItem *items[];
} GridMenu;

typedef struct
{
    void (*next_item)(const void *);
    void (*prev_item)(const void *);
    void (*select)(const void *);
    size_t selected_item;
    size_t num_items;
    MenuItem items[];
} VerticalMenu;

GridMenu *grid_menu_create(const size_t num_items, const size_t num_rows, const size_t num_cols);
void grid_menu_destroy(GridMenu *menu);

VerticalMenu *vertical_menu_create(const size_t num_items);
void vertical_menu_destroy(VerticalMenu *menu);
