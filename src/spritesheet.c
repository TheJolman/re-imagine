#include <raylib.h>

#include "spritesheet.h"

SpriteAnimation sprite_animation_create(Texture2D atlas, int frames_per_second,
                                        const Rectangle *rectangles, int length) {
    // Animation frame data is expected to be static/persistent (not allocated)
    SpriteAnimation sprite_anim = {
        .atlas = atlas,
        .frames_per_second = frames_per_second,
        .time_started = GetTime(),
        .rectangles = rectangles, // Store pointer to static data
        .rectangles_length = length,
    };

    return sprite_anim;
}

void sprite_animation_draw(SpriteAnimation animation, Rectangle dest, Vector2 origin,
                           float rotation, Color tint, float scale) {
    int index = (int)((GetTime() - animation.time_started) * animation.frames_per_second) %
                animation.rectangles_length;

    auto source = animation.rectangles[index];

    DrawTexturePro(animation.atlas, source, dest, origin, rotation, tint);
}

Texture2D sprite_animation_get_frame(const SpriteAnimation *anim, Rectangle *out_source) {
    if (!anim || anim->rectangles_length == 0 || !anim->rectangles) {
        if (out_source) {
            *out_source = (Rectangle){0, 0, 0, 0};
        }
        return (Texture2D){0};
    }

    int index =
        (int)((GetTime() - anim->time_started) * anim->frames_per_second) % anim->rectangles_length;

    if (out_source) {
        *out_source = anim->rectangles[index];
    }
    return anim->atlas;
}
