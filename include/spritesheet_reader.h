#pragma once

#include "components.h"
#include <raylib.h>

SpriteAnimation create_sprite_animation(Texture2D atlas, int framesPerSecond,
                                        Rectangle rectangles[], int length);
void dispose_sprite_animation(SpriteAnimation animation);
void draw_sprite_animation_pro(SpriteAnimation animation, Rectangle dest, Vector2 origin,
                               float rotation, Color tint, float scale);
Texture2D get_sprite_animation_current_frame(const SpriteAnimation *animation,
                                             Rectangle *outSource);
