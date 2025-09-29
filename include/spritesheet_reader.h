#pragma once

#include "components.h"
#include <raylib.h>

SpriteAnimation CreateSpriteAnimation(Texture2D atlas, int framesPerSecond, Rectangle rectangles[],
                                      int length);
void DisposeSpriteAnimation(SpriteAnimation animation);
void DrawSpriteAnimationPro(SpriteAnimation animation, Rectangle dest, Vector2 origin,
                            float rotation, Color tint, float scale);
Texture2D GetSpriteAnimationCurrentFrame(const SpriteAnimation *animation, Rectangle *outSource);
