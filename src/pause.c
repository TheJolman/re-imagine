#include "pause.h"
#include "raylib.h"

#define NUM_ITEMS 3

typedef struct {
  char *name;
  int posX;
  int posY;
  int fontSize;
  Color color;
} PauseItem;

const PauseItem pause_options = {"OPTIONS", 50, 100, 20, DARKGRAY};
const PauseItem pause_exit = {"EXIT", 50, 130, 20, DARKGRAY};
const PauseItem pause_credits = {"CREDITS", 50, 160, 20, DARKGRAY};

const PauseItem pauseItems[NUM_ITEMS] = {pause_options, pause_exit, pause_credits};

int currentMenuIndex = 0;

/**
 * adjusts current item without going out of bounds
 */
void adjustPauseMenuItem(int *currentPos, KeyboardKey key) {
  if (key == KEY_DOWN) {
    if (*currentPos == NUM_ITEMS - 1) {
      return;
    } else {
      *currentPos -= 1;
    }
  } else if (key == KEY_UP) {
    if (*currentPos == 0) {
      return;
    } else {
      *currentPos += 1;
    }
  }
}

void PauseMenu(void) {
  DrawText("PAUSE MENU", 50, 50, 40, DARKGRAY);

  for (int i = 0; i < NUM_ITEMS; ++i) {
    PauseItem item = pauseItems[i];
    DrawText(item.name, item.posX, item.posY, item.fontSize, item.color);
  }

  // DrawRectangleLines(40, 95, 300, 30, DARKGRAY);
  PauseItem currentItem = pauseItems[currentMenuIndex];
  DrawRectangleLines(currentItem.posX - 10, currentItem.posY - 5, 300, 30, DARKGRAY);
}
