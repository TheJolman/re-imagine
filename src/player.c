#include <raylib.h>
#include <raymath.h>

#include "components.h"
#include "player.h"
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

// Static animation frame data (persistent, not allocated)
static const Rectangle anim_frames_idle[] = {
    {SPRITE_FRAME_1, SPRITE_ROW_DOWN, SPRITE_TILE_SIZE, SPRITE_TILE_SIZE},
};

static const Rectangle anim_frames_right[] = {
    {SPRITE_FRAME_0, SPRITE_ROW_RIGHT, SPRITE_TILE_SIZE, SPRITE_TILE_SIZE},
    {SPRITE_FRAME_1, SPRITE_ROW_RIGHT, SPRITE_TILE_SIZE, SPRITE_TILE_SIZE},
};

static const Rectangle anim_frames_left[] = {
    {SPRITE_FRAME_0, SPRITE_ROW_LEFT, SPRITE_TILE_SIZE, SPRITE_TILE_SIZE},
    {SPRITE_FRAME_1, SPRITE_ROW_LEFT, SPRITE_TILE_SIZE, SPRITE_TILE_SIZE},
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

void _player_sprite_animation_create(Player *player) {
    player->anims.idle =
        sprite_animation_create(player->sprite_sheet, IDLE_ANIMATION_FPS, anim_frames_idle, 1);

    player->anims.right =
        sprite_animation_create(player->sprite_sheet, WALK_ANIMATION_FPS, anim_frames_right, 2);

    player->anims.left =
        sprite_animation_create(player->sprite_sheet, WALK_ANIMATION_FPS, anim_frames_left, 2);

    player->anims.up =
        sprite_animation_create(player->sprite_sheet, WALK_ANIMATION_FPS, anim_frames_up, 3);

    player->anims.down =
        sprite_animation_create(player->sprite_sheet, WALK_ANIMATION_FPS, anim_frames_down, 3);
}

/** Initializes the passed in player at game start
 */
void player_init(Player *player, const PlayerConfig *cfg) {
    player->position = cfg->init_position;
    player->speed = cfg->base_speed;
    player->sprint_modifier = cfg->sprint_modifier;
    player->size = cfg->size;
    player->sprite.rotation = 0.0f;
    player->sprite.tint = WHITE;
    player->sprite.scale = 1.0f;
    player->sprite_sheet = LoadTexture("assets/overworld/player.png");

    _player_sprite_animation_create(player);
    player->anims.current = &player->anims.idle;
}

void player_draw(const Player *player) {
    constexpr float SPRITE_CENTER_OFFSET = SPRITE_TILE_SIZE / 2.0f;
    Vector2 sprite_center = {SPRITE_CENTER_OFFSET, SPRITE_CENTER_OFFSET};

    Rectangle src = {};
    Texture2D atlas = sprite_animation_get_frame(player->anims.current, &src);
    if (atlas.id == 0) {
        return; // nothing to draw
    }

    auto pos = Vector2Add(player->position, sprite_center);
    auto size = (float)player->size;
    // destination rect in world coords, centered on player.position
    auto dest = (Rectangle){pos.x - size * 0.5f, pos.y - size * 0.5f, size * 2, size * 2};
    // centered point that will be aligned with dest when drawing
    auto origin = (Vector2){dest.width * 0.5f, dest.height * 0.5f};

    DrawTexturePro(atlas, src, dest, origin, player->sprite.rotation, player->sprite.tint);
}

void player_update(Player *player, Camera2D *camera) {
    // Vector2 prev_position = player->position;
    Vector2 move_vector = {};
    float current_speed = player->speed;

    auto anims = &player->anims; // alias for convenience
    if (IsKeyDown(KEY_LEFT_SHIFT)) {
        current_speed *= player->sprint_modifier;
    }
    if (IsKeyDown(KEY_W)) {
        move_vector.y -= 1.0f;
        anims->current = &anims->up;
    }
    if (IsKeyDown(KEY_S)) {
        move_vector.y += 1.0f;
        anims->current = &anims->down;
    }
    if (IsKeyDown(KEY_A)) {
        move_vector.x -= 1.0f;
        anims->current = &anims->left;
    }
    if (IsKeyDown(KEY_D)) {
        move_vector.x += 1.0f;
        anims->current = &anims->right;
    }

    if (Vector2Length(move_vector) > 0.0f) {
        move_vector = Vector2Normalize(move_vector);
        player->velocity = Vector2Scale(move_vector, current_speed);

        // TODO: check X and Y position separately for wall sliding
        player->position = Vector2Add(player->position, player->velocity);
    } else {
        player->velocity = (Vector2){};
        player->anims.current = &player->anims.idle;
    }

    camera->target = player->position;
}

void player_cleanup(Player *player) { UnloadTexture(player->sprite_sheet); }
