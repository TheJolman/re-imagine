/**
 * @file menu.h
 * @brief Menu system structures and functions
 */

#pragma once

#include "raylib.h"
#include "utils.h"
#include <stdint.h>

typedef enum
{
    MENU_LAYOUT_VERTICAL,
    MENU_LAYOUT_GRID,
} MenuLayoutType;

/**
 * @brief Individual menu item structure
 */
typedef struct
{
    const char *text;     ///< Text to display for this menu item
    int pos_x;            ///< X position for rendering
    int pos_y;            ///< Y position for rendering
    uint16_t font_size;   ///< Font size for text rendering
    Color color;          ///< Text color
    void (*select)(void); ///< Function to call when item is selected
} MenuItem;

/**
 * @brief Menu arranged in a grid layout
 */
typedef struct
{
    void (*move_left)(const void *);  ///< Function to handle left movement
    void (*move_right)(const void *); ///< Function to handle right movement
    void (*move_down)(const void *);  ///< Function to handle down movement
    void (*move_up)(const void *);    ///< Function to handle up movement
    uint16_t num_rows;                ///< Number of rows in the grid
    uint16_t num_cols;                ///< Number of columns in the grid
    uint16_t current_row;             ///< Currently selected row
    uint16_t current_col;             ///< Currently selected column
    uint16_t num_items;               ///< Total number of menu items
    MenuItem *items[];                ///< Array of menu item pointers
} GridMenu;

/**
 * @brief Menu arranged in a vertical list
 */
typedef struct
{
    void (*next_item)(const void *); ///< Function to move to next item
    void (*prev_item)(const void *); ///< Function to move to previous item
    void (*select)(const void *);    ///< Function to select current item
    uint16_t selected_item;          ///< Index of currently selected item
    uint16_t num_items;              ///< Total number of menu items
    MenuItem items[];                ///< Array of menu items
} VerticalMenu;

typedef struct
{
    const char *title;
    Rectangle rect;
    uint16_t font_size;
    MenuLayoutType layout;
    uint16_t num_rows; // For grid layout
    uint16_t num_cols; // For grid layout
} MenuConfig;

typedef struct
{
    MenuConfig config;
    void *menu_type; // Pointer to VerticalMenu or GridMenu
    uint16_t num_items;
    MenuItem *items;
} Menu;

Result menu_create(const MenuConfig *config, const char **item_texts,
                   void (**select_callbacks)(void), const uint16_t num_items);
void menu_destroy(Menu *menu);
void menu_handle_input(Menu *menu);
void menu_draw(const Menu *menu);
void menu_update_layout(Menu *menu);
