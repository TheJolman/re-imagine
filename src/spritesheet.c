#include <raylib.h>
#include <stdlib.h>

#include "arena.h"
#include "game.h"
#include "spritesheet.h"

SpriteAnimation sprite_animation_create(Texture2D atlas, int frames_per_second,
                                        Rectangle rectangles[], int length) {
    SpriteAnimation sprite_anim = {
        .atlas = atlas,
        .frames_per_second = frames_per_second,
        .time_started = GetTime(),
        .rectangles = NULL,
        .rectangles_length = length,
    };

    auto *rec = (Rectangle *)arena_alloc(&g_ctx.frame_arena, sizeof(Rectangle) * length);
    sprite_anim.rectangles = rec;

    for (int i = 0; i < length; i++) {
        sprite_anim.rectangles[i] = rectangles[i];
    }

    return sprite_anim;
}

void sprite_animation_destroy(SpriteAnimation anim) { free(anim.rectangles); }

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
