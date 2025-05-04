#ifndef PAUSE
#define PAUSE

extern int currentMenuIndex;

/**
 * Moves to the next item in the pause menu
 */
void nextMenuItem(int *currentPos);

/**
 * Moves to the previous item in the pause menu
 */
void prevMenuItem(int *currentPos);

/**
 * Displays the pause menu
 */
void PauseMenu(void);

/**
 * Selects an item in the pause menu
 */
void selectMenuItem(void);

#endif // !PAUSE
