#include "pause.h"
#include "assert.h"
#include "menu.h"
#include "raylib.h"
#include <stdlib.h>

static Menu *pause_menu = nullptr;

static void options_select(void) { return; } // TODO
static void exit_select(void)
{
    pause_menu_end();
    CloseWindow();
    exit(0);
}
static void credits_select(void) { return; } // TODO

static void pause_menu_create()
{
    const char *item_texts[] = {"OPTIONS", "EXIT", "CREDITS"};
    void (*select_callbacks[])(void) = {options_select, exit_select, credits_select};
    MenuConfig config = {
        .title = "PAUSE MENU",
        .rect = {50, 100, 300, 100},
        .font_size = 20,
        .layout = MENU_LAYOUT_VERTICAL,
    };

    Result res = menu_create(&config, item_texts, select_callbacks, 3);
    if (res.err)
    {
        error_log(res.err);
        return;
    }
    pause_menu = (Menu *)res.value;
}

void pause_menu_display(void)
{
    if (!pause_menu)
    {
        pause_menu_create();
    }

    menu_draw(pause_menu);
    menu_handle_input(pause_menu);
}

void pause_menu_end()
{
    if (pause_menu)
        menu_destroy(pause_menu);

    pause_menu = nullptr;
}
