#include "battle.h"
#include "map.h"
#include "raylib.h"

const int windowMargin = 50;
const int textHeight = 150;

extern Image frogeFrontImage;
extern Texture2D frogeFrontTexture;

const float frogeScale = 0.4f;
const Vector2 frogePosition = {40, 40};

void BattleScene(void) {
  DrawText("Battle scene is active!\nPress B to go back!", 50, 50, 20, DARKGRAY);

  // Draw text box
  DrawRectangleLines(windowMargin, screen.height - (windowMargin + textHeight),
                     screen.width - windowMargin * 2, textHeight, BLACK);

  // Draw square for enemy mon (art placeholder)
  DrawTextureEx(frogeFrontTexture, frogePosition, 0.0f, frogeScale, WHITE);

  // Draw hp bar for enemy mon

  // Draw square for players mon (art placeholder)
  DrawRectangle(screen.width - 440, screen.height - 440, 400, 300, BLUE);
  // Draw hp bar for players mon

  // Draw experience bar for players mon
}
