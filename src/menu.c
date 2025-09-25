#include "menu.h"
#include "utils.h"
#include <assert.h>

// GridMenu functions
static void _grid_menu_left(const void *menu_ptr)
{
    GridMenu *menu = (GridMenu *)menu_ptr;
    if (menu->current_col > 0)
        menu->current_col--;
    else
        menu->current_col = menu->num_cols - 1;
}

static void _grid_menu_right(const void *menu_ptr)
{
    GridMenu *menu = (GridMenu *)menu_ptr;
    if (menu->current_col < menu->num_cols - 1)
        menu->current_col++;
    else
        menu->current_col = 0;
}

static void _grid_menu_up(const void *menu_ptr)
{
    GridMenu *menu = (GridMenu *)menu_ptr;
    if (menu->current_row > 0)
        menu->current_row--;
    else
        menu->current_row = menu->num_rows - 1;
}

static void _grid_menu_down(const void *menu_ptr)
{
    GridMenu *menu = (GridMenu *)menu_ptr;
    if (menu->current_row < menu->num_rows - 1)
        menu->current_row++;
    else
        menu->current_row = 0;
}

static Result _grid_menu_create(const MenuConfig *config, const char **item_texts,
                                void (**select_callbacks)(void), const uint16_t num_items)
{
    GridMenu *menu = heap_list.malloc(sizeof(GridMenu) + num_items * sizeof(MenuItem *));
    if (!menu)
        return (Result){.err = "Could not allocate memory for GridMenu"};

    menu->num_items = num_items;
    menu->num_rows = config->num_rows;
    menu->num_cols = config->num_cols;
    menu->current_row = 0;
    menu->current_col = 0;
    menu->move_left = _grid_menu_left;
    menu->move_right = _grid_menu_right;
    menu->move_down = _grid_menu_down;
    menu->move_up = _grid_menu_up;

    for (uint16_t i = 0; i < num_items; i++)
    {
        MenuItem *item = heap_list.malloc(sizeof(MenuItem));
        if (!item)
            return (Result){.err = "Could not allocate memory for MenuItem"};
        item->text = item_texts[i];
        item->select = select_callbacks[i];
        item->font_size = config->font_size;
        item->color = DARKGRAY;
        menu->items[i] = item;
    }

    return (Result){.value = menu};
}

// VerticalMenu functions
static void _vertical_menu_next(const void *menu_ptr)
{
    VerticalMenu *menu = (VerticalMenu *)menu_ptr;
    if (menu->selected_item < menu->num_items - 1)
        menu->selected_item++;
    else
        menu->selected_item = 0;
}

static void _vertical_menu_prev(const void *menu_ptr)
{
    VerticalMenu *menu = (VerticalMenu *)menu_ptr;
    if (menu->selected_item > 0)
        menu->selected_item--;
    else
        menu->selected_item = menu->num_items - 1;
}

static Result _vertical_menu_create(const MenuConfig *config, const char **item_texts,
                                    void (**select_callbacks)(void), const uint16_t num_items)
{
    VerticalMenu *menu = heap_list.malloc(sizeof(VerticalMenu) + num_items * sizeof(MenuItem));
    if (!menu)
        return (Result){.err = "Could not allocate memory for VerticalMenu"};

    menu->num_items = num_items;
    menu->next_item = _vertical_menu_next;
    menu->prev_item = _vertical_menu_prev;
    menu->selected_item = 0;

    for (uint16_t i = 0; i < num_items; i++)
    {
        menu->items[i].text = item_texts[i];
        menu->items[i].select = select_callbacks[i];
        menu->items[i].font_size = config->font_size;
        menu->items[i].color = DARKGRAY;
    }

    return (Result){.value = menu};
}

static void _menu_calculate_layout(Menu *menu)
{
    // TODO: Parameterize these magic numbers
    float item_spacing = 30;
    float grid_item_width = 120;

    if (menu->config.layout == MENU_LAYOUT_VERTICAL)
    {
        VerticalMenu *v_menu = (VerticalMenu *)menu->menu_type;
        for (uint16_t i = 0; i < menu->num_items; i++)
        {
            v_menu->items[i].pos_x = menu->config.rect.x;
            v_menu->items[i].pos_y = menu->config.rect.y + i * item_spacing;
        }
    }
    else if (menu->config.layout == MENU_LAYOUT_GRID)
    {
        GridMenu *g_menu = (GridMenu *)menu->menu_type;
        for (uint16_t i = 0; i < g_menu->num_rows; i++)
        {
            for (uint16_t j = 0; j < g_menu->num_cols; j++)
            {
                uint16_t index = i * g_menu->num_cols + j;
                if (index < menu->num_items)
                {
                    g_menu->items[index]->pos_x = menu->config.rect.x + j * grid_item_width;
                    g_menu->items[index]->pos_y = menu->config.rect.y + i * item_spacing;
                }
            }
        }
    }
}

// Generic Menu functions
Result menu_create(const MenuConfig *config, const char **item_texts,
                   void (**select_callbacks)(void), const uint16_t num_items)
{
    Menu *menu = heap_list.malloc(sizeof(Menu));
    if (!menu)
        return (Result){.err = "Could not allocate memory for Menu"};

    menu->config = *config;
    menu->num_items = num_items;

    Result res;
    if (config->layout == MENU_LAYOUT_GRID)
    {
        res = _grid_menu_create(config, item_texts, select_callbacks, num_items);
    }
    else
    {
        res = _vertical_menu_create(config, item_texts, select_callbacks, num_items);
    }

    if (res.err)
    {
        heap_list.free(menu);
        return res;
    }

    menu->menu_type = res.value;

    _menu_calculate_layout(menu);

    return (Result){.value = menu};
}

void menu_destroy(Menu *menu)
{
    if (menu)
    {
        if (menu->menu_type)
        {
            if (menu->config.layout == MENU_LAYOUT_GRID)
            {
                GridMenu *g_menu = (GridMenu *)menu->menu_type;
                for (uint16_t i = 0; i < g_menu->num_items; i++)
                {
                    heap_list.free(g_menu->items[i]);
                }
            }
            heap_list.free(menu->menu_type);
        }
        heap_list.free(menu);
    }
}

void menu_handle_input(Menu *menu)
{
    if (!menu || !menu->menu_type)
        return;

    if (menu->config.layout == MENU_LAYOUT_VERTICAL)
    {
        VerticalMenu *v_menu = (VerticalMenu *)menu->menu_type;
        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
        {
            v_menu->next_item(v_menu);
        }
        else if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
        {
            v_menu->prev_item(v_menu);
        }
        else if (IsKeyPressed(KEY_ENTER))
        {
            v_menu->items[v_menu->selected_item].select();
        }
    }
    else if (menu->config.layout == MENU_LAYOUT_GRID)
    {
        GridMenu *g_menu = (GridMenu *)menu->menu_type;
        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
        {
            g_menu->move_down(g_menu);
        }
        else if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
        {
            g_menu->move_up(g_menu);
        }
        else if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
        {
            g_menu->move_left(g_menu);
        }
        else if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
        {
            g_menu->move_right(g_menu);
        }
        else if (IsKeyPressed(KEY_ENTER))
        {
            uint16_t index = g_menu->current_row * g_menu->num_cols + g_menu->current_col;
            if (index < g_menu->num_items)
            {
                g_menu->items[index]->select();
            }
        }
    }
}

void menu_draw(const Menu *menu)
{
    if (!menu || !menu->menu_type)
        return;

    DrawText(menu->config.title, menu->config.rect.x, menu->config.rect.y - 40, 40, DARKGRAY);

    if (menu->config.layout == MENU_LAYOUT_VERTICAL)
    {
        VerticalMenu *v_menu = (VerticalMenu *)menu->menu_type;
        for (uint16_t i = 0; i < v_menu->num_items; i++)
        {
            MenuItem item = v_menu->items[i];
            DrawText(item.text, item.pos_x, item.pos_y, item.font_size, item.color);
        }
        MenuItem currentItem = v_menu->items[v_menu->selected_item];
        DrawRectangleLines(currentItem.pos_x - 10, currentItem.pos_y - 5, 300, 30, DARKGRAY);
    }
    else if (menu->config.layout == MENU_LAYOUT_GRID)
    {
        GridMenu *g_menu = (GridMenu *)menu->menu_type;
        for (uint16_t i = 0; i < g_menu->num_items; i++)
        {
            MenuItem *item = g_menu->items[i];
            DrawText(item->text, item->pos_x, item->pos_y, item->font_size, item->color);
        }
        uint16_t index = g_menu->current_row * g_menu->num_cols + g_menu->current_col;
        if (index < g_menu->num_items)
        {
            MenuItem *currentItem = g_menu->items[index];
            DrawRectangleLines(currentItem->pos_x - 10, currentItem->pos_y - 5, 120, 30, DARKGRAY);
        }
    }
}

void menu_update_layout(Menu *menu)
{
    if (!menu)
        return;
    _menu_calculate_layout(menu);
}