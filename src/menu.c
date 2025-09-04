#include "menu.h"
#include "utils.h"
#include <assert.h>
#include <stdlib.h>

// TODO: do some extra math so empty squares can't get hovered
static void grid_menu_left(const void *menu_ptr)
{
    GridMenu *menu = (GridMenu *)menu_ptr;
    if (menu->current_col > 0)
        menu->current_col--;
    else
        menu->current_col = menu->num_cols - 1;
}

static void grid_menu_right(const void *menu_ptr)
{
    GridMenu *menu = (GridMenu *)menu_ptr;
    if (menu->current_col < menu->num_cols - 1)
        menu->current_col++;
    else
        menu->current_col = 0;
}

static void grid_menu_up(const void *menu_ptr)
{
    GridMenu *menu = (GridMenu *)menu_ptr;
    if (menu->current_row > 0)
        menu->current_row--;
    else
        menu->current_row = menu->num_rows - 1;
}

static void grid_menu_down(const void *menu_ptr)
{
    GridMenu *menu = (GridMenu *)menu_ptr;
    if (menu->current_row < menu->num_rows - 1)
        menu->current_row++;
    else
        menu->current_row = 0;
}

Result grid_menu_create(uint16_t num_items, const uint16_t num_rows, const uint16_t num_cols)
{
    GridMenu *menu = heap_list.malloc(sizeof(GridMenu) + num_items * sizeof(MenuItem *));
    if (!menu)
        return (Result){.err = "Could not allocate memory for GridMenu"};

    menu->num_items = num_items;
    menu->num_rows = num_rows;
    menu->num_cols = num_cols;
    menu->current_row = 0;
    menu->current_col = 0;
    menu->move_left = grid_menu_left;
    menu->move_right = grid_menu_right;
    menu->move_down = grid_menu_down;
    menu->move_up = grid_menu_up;

    return (Result){.value = menu};
}

void grid_menu_destroy(GridMenu *menu) { heap_list.free(menu); }

static void vertical_menu_next(const void *menu_ptr)
{
    VerticalMenu *menu = (VerticalMenu *)menu_ptr;

    if (menu->selected_item < menu->num_items - 1)
        menu->selected_item++;
    else
        menu->selected_item = 0;
}

static void vertical_menu_prev(const void *menu_ptr)
{
    VerticalMenu *menu = (VerticalMenu *)menu_ptr;

    if (menu->selected_item > 0)
        menu->selected_item--;
    else
        menu->selected_item = menu->num_items - 1;
}

VerticalMenu *vertical_menu_create(const uint16_t num_items)
{
    // TODO: Utilize result type here
    VerticalMenu *menu = heap_list.malloc(sizeof(VerticalMenu) + num_items * sizeof(MenuItem));
    if (!menu)
        return nullptr;

    menu->num_items = num_items;
    menu->next_item = vertical_menu_next;
    menu->prev_item = vertical_menu_prev;
    menu->selected_item = 0;
    return menu;
}

void vertical_menu_destroy(VerticalMenu *menu) { heap_list.free(menu); }
