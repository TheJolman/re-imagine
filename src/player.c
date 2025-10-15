#include "player.h"
#include "collision.h"
#include "components.h"
#include "debug.h"
#include "game.h"
#include "spritesheet_reader.h"
#include <raylib.h>
#include <raymath.h>

PlayerAnimations anims = {};
// SpriteAnimation _walk_right_animation;
// SpriteAnimation _walk_left_animation;
// SpriteAnimation _walk_up_animation;
// SpriteAnimation _walk_down_animation;
// SpriteAnimation _idle_animation;
// SpriteAnimation curr_animation = {0};

void create_player_sprite_animation(void)
{
    Game_ctx.player.sprite_sheet = LoadTexture("assets/sample-assets/Texture/mario.png");
    anims.idle = create_sprite_animation(Game_ctx.player.sprite_sheet, 1,
                                         (Rectangle[]){
                                             (Rectangle){32, 0, 32, 32},
                                         },
                                         1);
    anims.right = create_sprite_animation(Game_ctx.player.sprite_sheet, 6,
                                          (Rectangle[]){
                                              (Rectangle){0, 96, 32, 32},
                                              (Rectangle){32, 96, 32, 32},
                                              (Rectangle){64, 96, 32, 32},
                                          },
                                          2);
    anims.left = create_sprite_animation(Game_ctx.player.sprite_sheet, 6,
                                         (Rectangle[]){
                                             (Rectangle){0, 64, 32, 32},
                                             (Rectangle){32, 64, 32, 32},
                                             (Rectangle){64, 64, 32, 32},
                                         },
                                         2);
    anims.up = create_sprite_animation(Game_ctx.player.sprite_sheet, 6,
                                       (Rectangle[]){
                                           (Rectangle){0, 32, 32, 32},
                                           (Rectangle){32, 32, 32, 32},
                                           (Rectangle){64, 32, 32, 32},
                                       },
                                       3);
    anims.down = create_sprite_animation(Game_ctx.player.sprite_sheet, 6,
                                         (Rectangle[]){
                                             (Rectangle){0, 0, 32, 32},
                                             (Rectangle){32, 0, 32, 32},
                                             (Rectangle){64, 0, 32, 32},
                                         },
                                         3);
}

void update_player_draw_frame(Vector2 positionw)
{
    // Get current frame source rect and atlas
    Rectangle src;
    Texture2D atlas = get_sprite_animation_current_frame(anims.current, &src);
    if (atlas.id == 0)
        return; // nothing to draw

    // Destination rectangle in world coordinates (centered on player.position)
    float size = (float)Game_ctx.player.size;
    Rectangle dest = {positionw.x - size * 0.5f, positionw.y - size * 0.5f, size * 2, size * 2};

    // origin is the point in dest that will be aligned with dest.x/y when drawing;
    // use the center so rotation/placement is correct
    Vector2 origin = {dest.width * 0.5f, dest.height * 0.5f};

    DrawTexturePro(atlas, src, dest, origin, Game_ctx.player.sprite.rotation,
                   Game_ctx.player.sprite.tint);
}

void _player_draw(void)
{
    // Draw player

    Vector2 sprite_center = {
        (float)32 / 2,
        (float)32 / 2,

    };

    update_player_draw_frame(Vector2Add(Game_ctx.player.position, sprite_center));

    /*DrawTextureEx(Game_ctx.player.sprite.texture, Vector2Subtract(Game_ctx.player.position,
       sprite_center), Game_ctx.player.sprite.rotation, Game_ctx.player.sprite.scale,
       Game_ctx.player.sprite.tint);
                   */

#ifdef DEBUG
    draw_debug_info();
    DrawLine((int)Game_ctx.camera.target.x, -GetScreenHeight() * 10, (int)Game_ctx.camera.target.x,
             GetScreenHeight() * 10, ORANGE);
    // DrawLine(-GetScreenWidth() * 10, (int)Game_ctx.camera.target.y, GetScreenWidth() * 10,
    //(int)Game_ctx.camera.target.y, ORANGE);

#endif
}

void draw_debug_info(void)
{
    // Get camera and player position as strings
    char playerPosText[64];
    char cameraPosText[64];

    sprintf(playerPosText, "Player Pos: (%.2f, %.2f)", Game_ctx.player.position.x,
            Game_ctx.player.position.y);
    sprintf(cameraPosText, "Camera Pos: (%.2f, %.2f)", Game_ctx.camera.target.x,
            Game_ctx.camera.target.y);

    // Draw text to screen (top-left corner)
    DrawText(playerPosText, 10, 10, 20, RED);
    DrawText(cameraPosText, 10, 35, 20, GREEN);
}

void _player_move(void)
{
    Vector2 prev_position = Game_ctx.player.position; // stored for collision handling

    // Determine base speed and apply sprint modifier
    float current_speed = Game_cfg.player_base_speed;
    if (IsKeyDown(KEY_LEFT_SHIFT))
    {
        current_speed *= Game_cfg.player_sprint_modifier;
    }

    // Get movement direction from input
    Vector2 move_vector = {0};
    if (IsKeyDown(KEY_W))
    {
        move_vector.y -= 1.0f;
        anims.current = &anims.up;
    }

    if (IsKeyDown(KEY_S))
    {
        move_vector.y += 1.0f;
        anims.current = &anims.down;
    }

    if (IsKeyDown(KEY_A))
    {
        move_vector.x -= 1.0f;
        anims.current = &anims.left;
    }

    if (IsKeyDown(KEY_D))
    {

        move_vector.x += 1.0f;
        anims.current = &anims.right;
    }

    if (Vector2Length(move_vector) > 0.0f)
    {
        // Normalize the vector to get a pure direction, then scale by speed
        move_vector = Vector2Normalize(move_vector);
        Game_ctx.player.velocity.vec = Vector2Scale(move_vector, current_speed);

        // Solution for sliding: check X and Y positions separately
        // Try x-axis movement first
        Game_ctx.player.position.x += Game_ctx.player.velocity.vec.x;
        update_player_collision_box(&Game_ctx.player);

        if (check_map_collision(Game_ctx.map, Game_ctx.player.collision_box))
        {
            // x axis collision --> revert x position
            Game_ctx.player.position.x = prev_position.x;
            update_player_collision_box(&Game_ctx.player);
        }

        // Now check Y axis
        Game_ctx.player.position.y += Game_ctx.player.velocity.vec.y;
        update_player_collision_box(&Game_ctx.player);

        if (check_map_collision(Game_ctx.map, Game_ctx.player.collision_box))
        {
            Game_ctx.player.position.y = prev_position.y;
            update_player_collision_box(&Game_ctx.player);
        }

        // Update final velocity based on actual movement
        Vector2 actual_movement = Vector2Subtract(Game_ctx.player.position, prev_position);
        Game_ctx.player.velocity.vec = actual_movement;
    }
    else
    {
        // No movement input, so velocity is zero
        Game_ctx.player.velocity.vec = (Vector2){0};
        anims.current = &anims.idle;
    }

    // Camera always follows the player's position
    Game_ctx.camera.target = Game_ctx.player.position;
}
