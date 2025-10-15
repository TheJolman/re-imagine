#include "spritesheet_reader.h"
#include "raylib.h"
#include "utils.h"
#include <stdlib.h>

SpriteAnimation create_sprite_animation(Texture2D atlas, int framesPerSecond,
                                        Rectangle rectangles[], int length)
{
    SpriteAnimation spriteAnimation = {.atlas = atlas,
                                       .framesPerSecond = framesPerSecond,
                                       .timeStarted = GetTime(),
                                       .rectangles = NULL,
                                       .rectanglesLength = length};

    Rectangle *mem = (Rectangle *)heap_list.malloc(sizeof(Rectangle) * length);
    if (mem == NULL)
    {
        TraceLog(LOG_FATAL, "No memory for create_sprite_animation");
        spriteAnimation.rectanglesLength = 0;
        return spriteAnimation;
    }

    spriteAnimation.rectangles = mem;

    for (int i = 0; i < length; i++)
    {
        spriteAnimation.rectangles[i] = rectangles[i];
    }

    return spriteAnimation;
}

void dispose_sprite_animation(SpriteAnimation animation) { heap_list.free(animation.rectangles); }

void draw_sprite_animation_pro(SpriteAnimation animation, Rectangle dest, Vector2 origin,
                               float rotation, Color tint, float scale)
{
    int index = (int)((GetTime() - animation.timeStarted) * animation.framesPerSecond) %
                animation.rectanglesLength;

    Rectangle source = animation.rectangles[index];

    DrawTexturePro(animation.atlas, source, dest, origin, rotation, tint);
}
Texture2D get_sprite_animation_current_frame(const SpriteAnimation *animation, Rectangle *outSource)
{
    if (animation == NULL || animation->rectanglesLength == 0 || animation->rectangles == NULL)
    {
        if (outSource)
            *outSource = (Rectangle){0, 0, 0, 0};
        return (Texture2D){0};
    }

    int index = (int)((GetTime() - animation->timeStarted) * animation->framesPerSecond) %
                animation->rectanglesLength;
    if (outSource)
        *outSource = animation->rectangles[index];
    return animation->atlas;
}