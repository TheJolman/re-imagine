#include <stdlib.h>
#include <raylib.h>

#include "spritesheet.h"

SpriteAnimation sprite_animation_create(Texture2D atlas, int frames_per_second,
                                        Rectangle rectangles[], int length) {
    SpriteAnimation sprite_anim = {
        .atlas = atlas,
        .frames_per_second = frames_per_second,
        .time_started = GetTime(),
        .rectangles = NULL,
        .rectangles_lenght = length,
    };

    // TODO: mem allocator
}
