#define SPRITESHEET_READER_H

#include <raylib.h>


typedef struct {
    Texture2D atlas;
    int framePerSecond;
    int spriteH;
    Rectangle* rectangles;
    int RectanglesLength;
} SpriteAnimation;

void DrawSpriteAnimationPro(SpriteAnimation animation, Rectangle dest, Vector2 origin, floa
t rotation, Color tint);