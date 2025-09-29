#include "player.h"
#include "components.h"
#include "debug.h"
#include "game.h"
#include "spritesheet_reader.h"
#include <raylib.h>
#include <raymath.h>

Texture2D _player_sprite_sheet;
SpriteAnimation _walk_right_animation;
SpriteAnimation _walk_left_animation;
SpriteAnimation _walk_up_animation;
SpriteAnimation _walk_down_animation;
SpriteAnimation _idle_animation;
SpriteAnimation _animation = {0};

void CreatePlayerSpriteAnimation(void)
{
    _player_sprite_sheet = LoadTexture("assets/sample-assets/Texture/mario.png");
    _idle_animation = CreateSpriteAnimation(_player_sprite_sheet, 1,
                                            (Rectangle[]){
                                                (Rectangle){32, 0, 32, 32},
                                            },
                                            1);
    _walk_right_animation = CreateSpriteAnimation(_player_sprite_sheet, 3,
                                                  (Rectangle[]){
                                                      (Rectangle){0, 96, 32, 32},
                                                      (Rectangle){32, 96, 32, 32},
                                                      (Rectangle){64, 96, 32, 32},
                                                  },
                                                  2);
    _walk_left_animation = CreateSpriteAnimation(_player_sprite_sheet, 3,
                                                 (Rectangle[]){
                                                     (Rectangle){0, 64, 32, 32},
                                                     (Rectangle){32, 64, 32, 32},
                                                     (Rectangle){64, 64, 32, 32},
                                                 },
                                                 2);
    _walk_up_animation = CreateSpriteAnimation(_player_sprite_sheet, 3,
                                               (Rectangle[]){
                                                   (Rectangle){0, 32, 32, 32},
                                                   (Rectangle){32, 32, 32, 32},
                                                   (Rectangle){64, 32, 32, 32},
                                               },
                                               3);
    _walk_down_animation = CreateSpriteAnimation(_player_sprite_sheet, 3,
                                                 (Rectangle[]){
                                                     (Rectangle){0, 0, 32, 32},
                                                     (Rectangle){32, 0, 32, 32},
                                                     (Rectangle){64, 0, 32, 32},
                                                 },
                                                 3);
}

void UpdatePlayerDrawFrame(Vector2 positionw)
{
    // Get current frame source rect and atlas
    Rectangle src;
    Texture2D atlas = GetSpriteAnimationCurrentFrame(&_animation, &src);
    if (atlas.id == 0)
        return; // nothing to draw

    // Destination rectangle in world coordinates (centered on player.position)
    float size = (float)ctx.player.size;
    Rectangle dest = {positionw.x - size * 0.5f, positionw.y - size * 0.5f, size * 2, size * 2};

    // origin is the point in dest that will be aligned with dest.x/y when drawing;
    // use the center so rotation/placement is correct
    Vector2 origin = {dest.width * 0.5f, dest.height * 0.5f};

    DrawTexturePro(atlas, src, dest, origin, ctx.player.sprite.rotation, ctx.player.sprite.tint);
}

void _player_draw(void)
{
    // Draw player

    Vector2 sprite_center = {
        (float)32 / 2,
        (float)32 / 2,

    };

    UpdatePlayerDrawFrame(Vector2Add(ctx.player.position, sprite_center));

    /*DrawTextureEx(ctx.player.sprite.texture, Vector2Subtract(ctx.player.position, sprite_center),
                   ctx.player.sprite.rotation, ctx.player.sprite.scale, ctx.player.sprite.tint);
                   */

#ifdef DEBUG
    DrawDebugInfo();
    DrawLine((int)ctx.camera.target.x, -GetScreenHeight() * 10, (int)ctx.camera.target.x,
             GetScreenHeight() * 10, ORANGE);
    // DrawLine(-GetScreenWidth() * 10, (int)ctx.camera.target.y, GetScreenWidth() * 10,
    //(int)ctx.camera.target.y, ORANGE);

#endif
}

void DrawDebugInfo(void)
{
    // Get camera and player position as strings
    char playerPosText[64];
    char cameraPosText[64];

    sprintf(playerPosText, "Player Pos: (%.2f, %.2f)", ctx.player.position.x,
            ctx.player.position.y);
    sprintf(cameraPosText, "Camera Pos: (%.2f, %.2f)", ctx.camera.target.x, ctx.camera.target.y);

    // Draw text to screen (top-left corner)
    DrawText(playerPosText, 10, 10, 20, RED);
    DrawText(cameraPosText, 10, 35, 20, GREEN);
}

void _player_move(void)
{

    // Determine base speed and apply sprint modifier
    float current_speed = cfg.player_base_speed;
    if (IsKeyDown(KEY_LEFT_SHIFT))
    {
        current_speed *= cfg.player_sprint_modifier;
    }

    // Get movement direction from input
    Vector2 move_vector = {0};
    if (IsKeyDown(KEY_W))
    {
        move_vector.y -= 1.0f;
        _animation = _walk_up_animation;
    }

    if (IsKeyDown(KEY_S))
    {
        move_vector.y += 1.0f;
        _animation = _walk_down_animation;
    }

    if (IsKeyDown(KEY_A))
    {
        move_vector.x -= 1.0f;
        _animation = _walk_left_animation;
    }

    if (IsKeyDown(KEY_D))
    {

        move_vector.x += 1.0f;
        _animation = _walk_right_animation;
    }

    if (Vector2Length(move_vector) > 0.0f)
    {
        // Normalize the vector to get a pure direction, then scale by speed
        move_vector = Vector2Normalize(move_vector);
        ctx.player.velocity.vec = Vector2Scale(move_vector, current_speed);
        ctx.player.position = Vector2Add(ctx.player.position, ctx.player.velocity.vec);
    }
    else
    {
        // No movement input, so velocity is zero
        ctx.player.velocity.vec = (Vector2){0};
        _animation = _idle_animation;
    }

    // Camera always follows the player's position
    ctx.camera.target = ctx.player.position;
}