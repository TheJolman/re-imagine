#ifndef PAUSE
#define PAUSE

#include "raylib.h"

extern int currentMenuIndex;

void adjustPauseMenuItem(int *currentPos, KeyboardKey key);
void PauseMenu(void);

#endif // !PAUSE
