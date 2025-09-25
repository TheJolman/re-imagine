#define SPRITESHEET_READER_H

#include <raylib.h>


typedef struct {
    Texture2D atlas;
    int framesPerSecond;
    float timeStarted;
    int spriteH;
    Rectangle* rectangles;
    int rectanglesLength;
} SpriteAnimation;

SpriteAnimation CreateSpriteAnimation(Texture2D atlas, int framesPerSecond, Rectangle rectangles[], int length);
void DisposeSpriteAnimation(SpriteAnimation animation);
void DrawSpriteAnimationPro(SpriteAnimation animation, Rectangle dest, Vector2 origin, float rotation, Color tint);
 