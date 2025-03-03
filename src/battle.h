#ifndef BATTLE
#define BATTLE

#include "raylib.h"

typedef struct {
  Texture2D frontTexture;
  Texture2D backTexture;
  float scale;
  Color tint;
} MonTexture;

extern MonTexture froge;

void BattleScene(void);

#endif // !BATTLE
