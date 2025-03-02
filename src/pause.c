#include "pause.h"
#include "assert.h"
#include "raylib.h"

#define NUM_ITEMS 3

typedef struct {
  char *name;
  int posX;
  int posY;
  int fontSize;
  Color color;
} PauseItem;

typedef enum { OPTIONS, EXIT, CREDITS } MenuIndices;

const PauseItem pause_options = {"OPTIONS", 50, 100, 20, DARKGRAY};
const PauseItem pause_exit = {"EXIT", 50, 130, 20, DARKGRAY};
const PauseItem pause_credits = {"CREDITS", 50, 160, 20, DARKGRAY};

const PauseItem pauseItems[NUM_ITEMS] = {pause_options, pause_exit, pause_credits};

int currentMenuIndex = 0;

void nextMenuItem(int *currentPos) {
  if (*currentPos == NUM_ITEMS - 1) {
    *currentPos = 0;
  } else {
    *currentPos += 1;
  }
}

void prevMenuItem(int *currentPos) {
  if (*currentPos == 0) {
    *currentPos = NUM_ITEMS - 1;
  } else {
    *currentPos -= 1;
  }
}

void PauseMenu(void) {
  DrawText("PAUSE MENU", 50, 50, 40, DARKGRAY);

  for (int i = 0; i < NUM_ITEMS; ++i) {
    PauseItem item = pauseItems[i];
    DrawText(item.name, item.posX, item.posY, item.fontSize, item.color);
  }

  assert(currentMenuIndex >= 0 && currentMenuIndex < NUM_ITEMS);
  PauseItem currentItem = pauseItems[currentMenuIndex];
  DrawRectangleLines(currentItem.posX - 10, currentItem.posY - 5, 300, 30, DARKGRAY);
}

void selectMenuItem(void) {
  assert(currentMenuIndex >= 0 && currentMenuIndex < NUM_ITEMS);

  switch (currentMenuIndex) {
  case OPTIONS:
    break;
  case EXIT:
    CloseWindow();
    break;
  case CREDITS:
    break;
  }
}
