#include "battle.h"
#include "map.h"
#include "raylib.h"

const int windowMargin = 50;
const int textHeight = 150;

// extern Image frogeFrontImage;
// extern Texture2D frogeFrontTexture;
// const float frogeScale = 0.4f;

void BattleScene(void) {
  DrawText("Battle scene is active!\nPress B to go back!", 50, 50, 20, DARKGRAY);

  const Vector2 enemyPosition = {40, 40};
  const Vector2 playerPosition = {screen.width - 500, screen.height - 500};

  // Draw text box
  DrawRectangleLines(windowMargin, screen.height - (windowMargin + textHeight),
                     screen.width - windowMargin * 2, textHeight, BLACK);

  // Draw square for enemy mon (art placeholder)
  DrawTextureEx(froge.frontTexture, enemyPosition, 0.0f, froge.scale, WHITE);

  // Draw hp bar for enemy mon

  // Draw square for players mon (art placeholder)
  DrawRectangle(screen.width - 440, screen.height - 440, 400, 300, BLUE);
  DrawTextureEx(froge.backTexture, playerPosition, 0.0f, froge.scale, WHITE);
  // Draw hp bar for players mon

  // Draw experience bar for players mon
}
