#include <raylib.h>
#include <raymath.h>

#include "components.h"
#include "game.h"
#include "spritesheet.h"

// Sprite sheet constants
constexpr int SPRITE_TILE_SIZE = 32;
constexpr int SPRITE_ROW_DOWN = 0;
constexpr int SPRITE_ROW_UP = 32;
constexpr int SPRITE_ROW_LEFT = 64;
constexpr int SPRITE_ROW_RIGHT = 96;

constexpr int SPRITE_FRAME_0 = 0;
constexpr int SPRITE_FRAME_1 = 32;
constexpr int SPRITE_FRAME_2 = 64;

constexpr int WALK_ANIMATION_FPS = 6;
constexpr int IDLE_ANIMATION_FPS = 1;

constexpr PlayerConfig cfg = {
    .base_speed = 5.0f,
    .sprint_modifier = 2.0f,
    .init_position = (Position){100, 100},
    .size = 30, // collider size
};

// Static animation frame data (persistent, not allocated)
static const Rectangle anim_frames_idle[] = {
    {SPRITE_FRAME_1, SPRITE_ROW_DOWN, SPRITE_TILE_SIZE, SPRITE_TILE_SIZE},
};

static const Rectangle anim_frames_right[] = {
    {SPRITE_FRAME_0, SPRITE_ROW_RIGHT, SPRITE_TILE_SIZE, SPRITE_TILE_SIZE},
    {SPRITE_FRAME_1, SPRITE_ROW_RIGHT, SPRITE_TILE_SIZE, SPRITE_TILE_SIZE},
    {SPRITE_FRAME_2, SPRITE_ROW_RIGHT, SPRITE_TILE_SIZE, SPRITE_TILE_SIZE},
};

static const Rectangle anim_frames_left[] = {
    {SPRITE_FRAME_0, SPRITE_ROW_LEFT, SPRITE_TILE_SIZE, SPRITE_TILE_SIZE},
    {SPRITE_FRAME_1, SPRITE_ROW_LEFT, SPRITE_TILE_SIZE, SPRITE_TILE_SIZE},
    {SPRITE_FRAME_2, SPRITE_ROW_LEFT, SPRITE_TILE_SIZE, SPRITE_TILE_SIZE},
};

static const Rectangle anim_frames_up[] = {
    {SPRITE_FRAME_0, SPRITE_ROW_UP, SPRITE_TILE_SIZE, SPRITE_TILE_SIZE},
    {SPRITE_FRAME_1, SPRITE_ROW_UP, SPRITE_TILE_SIZE, SPRITE_TILE_SIZE},
    {SPRITE_FRAME_2, SPRITE_ROW_UP, SPRITE_TILE_SIZE, SPRITE_TILE_SIZE},
};

static const Rectangle anim_frames_down[] = {
    {SPRITE_FRAME_0, SPRITE_ROW_DOWN, SPRITE_TILE_SIZE, SPRITE_TILE_SIZE},
    {SPRITE_FRAME_1, SPRITE_ROW_DOWN, SPRITE_TILE_SIZE, SPRITE_TILE_SIZE},
    {SPRITE_FRAME_2, SPRITE_ROW_DOWN, SPRITE_TILE_SIZE, SPRITE_TILE_SIZE},
};

void _player_sprite_animation_create() {
    auto anims = &g_ctx.player.anims;

    anims->idle = sprite_animation_create(g_ctx.player.sprite_sheet, IDLE_ANIMATION_FPS,
                                          anim_frames_idle, 1);

    anims->right = sprite_animation_create(g_ctx.player.sprite_sheet, WALK_ANIMATION_FPS,
                                           anim_frames_right, 3);

    anims->left = sprite_animation_create(g_ctx.player.sprite_sheet, WALK_ANIMATION_FPS,
                                          anim_frames_left, 3);

    anims->up = sprite_animation_create(g_ctx.player.sprite_sheet, WALK_ANIMATION_FPS,
                                        anim_frames_up, 3);

    anims->down = sprite_animation_create(g_ctx.player.sprite_sheet, WALK_ANIMATION_FPS,
                                          anim_frames_down, 3);
}

void player_init() {
    Player player = {};
    player.position = cfg.init_position;
    player.velocity.max_speed = cfg.base_speed;
    player.size = cfg.size;
    player.sprite.rotation = 0.0f;
    player.sprite.tint = WHITE;
    player.sprite.scale = 1.0f;
    player.sprite_sheet = LoadTexture("assets/overworld/player.png");

    g_ctx.player = player;
    _player_sprite_animation_create();
    g_ctx.player.anims.current = &g_ctx.player.anims.idle;
}

void player_draw() {
    constexpr float SPRITE_CENTER_OFFSET = SPRITE_TILE_SIZE / 2.0f;
    Vector2 sprite_center = {SPRITE_CENTER_OFFSET, SPRITE_CENTER_OFFSET};

    Rectangle src = {};
    Texture2D atlas = sprite_animation_get_frame(g_ctx.player.anims.current, &src);
    if (atlas.id == 0) {
        return; // nothing to draw
    }

    auto pos = Vector2Add(g_ctx.player.position, sprite_center);
    auto size = (float)g_ctx.player.size;
    // destination rect in world coords, centered on player.position
    auto dest = (Rectangle){pos.x - size * 0.5f, pos.y - size * 0.5f, size * 2, size * 2};
    // centered point that will be aligned with dest when drawing
    auto origin = (Vector2){dest.width * 0.5f, dest.height * 0.5f};

    DrawTexturePro(atlas, src, dest, origin, g_ctx.player.sprite.rotation,
                   g_ctx.player.sprite.tint);
}

void player_input_handler(Vector2 *move_vector, Vector2 *prev_position, float *current_speed) {
    auto anims = &g_ctx.player.anims;
    if (IsKeyDown(KEY_LEFT_SHIFT)) {
        *current_speed *= cfg.sprint_modifier;
    }
    if (IsKeyDown(KEY_W)) {
        move_vector->y -= 1.0f;
        anims->current = &anims->up;
    }
    if (IsKeyDown(KEY_S)) {
        move_vector->y += 1.0f;
        anims->current = &anims->down;
    }
    if (IsKeyDown(KEY_A)) {
        move_vector->x -= 1.0f;
        anims->current = &anims->left;
    }
    if (IsKeyDown(KEY_D)) {
        move_vector->x += 1.0f;
        anims->current = &anims->right;
    }
}

void player_move() {
    Vector2 move_vector = {};
    Vector2 prev_position = g_ctx.player.position;
    float current_speed = cfg.base_speed;
    player_input_handler(&move_vector, &prev_position, &current_speed);

    if (Vector2Length(move_vector) > 0.0f) {
        move_vector = Vector2Normalize(move_vector);
        g_ctx.player.velocity.vec = Vector2Scale(move_vector, current_speed);

        // Solution for wall sliding: check X and Y position separately
        g_ctx.player.position.x += g_ctx.player.velocity.vec.x;
        // TODO:  player_update_collision_box();

        // actual movement
        g_ctx.player.velocity.vec = Vector2Subtract(g_ctx.player.position, prev_position);
    } else {
        g_ctx.player.velocity.vec = (Vector2){};
        g_ctx.player.anims.current = &g_ctx.player.anims.idle;
    }

    g_ctx.camera.target = g_ctx.player.position;
}

void player_cleanup() { UnloadTexture(g_ctx.player.sprite_sheet); }
