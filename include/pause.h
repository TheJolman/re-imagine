#pragma once

// extern int currentMenuIndex;

/**
 * Moves to the next item in the pause menu
 */
void pauseMenuNext(int *currentPos);

/**
 * Moves to the previous item in the pause menu
 */
void pauseMenuPrev(int *currentPos);

/**
 * Displays the pause menu
 */
void pauseMenuDisplay(void);

/**
 * Selects an item in the pause menu
 */
void pauseMenuSelect(void);
