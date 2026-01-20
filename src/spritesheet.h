#pragma once

#include <raylib.h>

#include "components.h"

SpriteAnimation sprite_animation_create(Texture2D atlas, int frames_per_second,
                                        Rectangle rectangles[], int length);

void sprite_animation_destroy(SpriteAnimation animation);

void sprite_animation_draw(SpriteAnimation animation, Rectangle dest, Vector2 origin,
                               float rotation, Color tint, float scale);

Texture2D sprite_animation_get_frame(const SpriteAnimation *animation,
                                             Rectangle *out_source);
