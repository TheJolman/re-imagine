#include "player.h"
#include <raylib.h>
#include <raymath.h>
#include "spritesheet_reader.h"
#include "game.h"	
#include "debug.h"



Texture2D _player_sprite_sheet;
SpriteAnimation _walk_right_animation;
SpriteAnimation _walk_left_animation;
SpriteAnimation _walk_up_animation;
SpriteAnimation _walk_down_animation;
SpriteAnimation _animation = { 0 };



void CreatePlayerSpriteAnimation(void)
{
    _player_sprite_sheet = LoadTexture("assets/sample-assets/Texture/mario.png");
	_walk_right_animation = CreateSpriteAnimation(_player_sprite_sheet, 3, (Rectangle[]) {
		(Rectangle){0, 0, 32, 32},
		(Rectangle){32, 0, 32, 32},
		(Rectangle){64, 0, 32, 32},
	}, 3);

}

void UpdatePlayerDrawFrame(void)
{
	BeginDrawing();

		ClearBackground(RAYWHITE);

		Rectangle dest = { 32, 32, 512, 512 };
		Vector2 origin = { 0 };
		DrawSpriteAnimationPro( _walk_right_animation, dest, origin, 0, WHITE);

	EndDrawing();
}

void _player_draw(void)
{
    // Draw player
    Vector2 sprite_center = {
        (float)ctx.player.sprite.texture.width * ctx.player.sprite.scale / 2.0f,
        (float)ctx.player.sprite.texture.height * ctx.player.sprite.scale / 2.0f,
    };
    DrawTextureEx(ctx.player.sprite.texture, Vector2Subtract(ctx.player.position, sprite_center),
                  ctx.player.sprite.rotation, ctx.player.sprite.scale, ctx.player.sprite.tint);
#ifdef DEBUG
    DrawLine((int)ctx.camera.target.x, -GetScreenHeight() * 10, (int)ctx.camera.target.x,
             GetScreenHeight() * 10, ORANGE);
    DrawLine(-GetScreenWidth() * 10, (int)ctx.camera.target.y, GetScreenWidth() * 10,
             (int)ctx.camera.target.y, ORANGE);
#endif
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
        move_vector.y -= 1.0f;
    if (IsKeyDown(KEY_S))
        move_vector.y += 1.0f;
    if (IsKeyDown(KEY_A))
        move_vector.x -= 1.0f;
    if (IsKeyDown(KEY_D))
        move_vector.x += 1.0f;

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
    }

    // Camera always follows the player's position
    ctx.camera.target = ctx.player.position;
}