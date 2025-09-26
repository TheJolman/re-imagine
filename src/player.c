#include "player.h"

#include <raylib.h>
#include <raymath.h>
#include "spritesheet_reader.h"




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