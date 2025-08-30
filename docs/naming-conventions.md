# Naming Conventions

This document outlines the naming conventions used throughout the RPG Raylib project.

## General Principles

- Use descriptive, meaningful names
- Avoid abbreviations unless they are well-established (e.g., `hp` for health points)
- Prefer clarity over brevity
- Be consistent within the same scope/module

## Functions

**Rule**: Use `snake_case` for all function names

```c
// ✅ Good
void init_game(void);
void update_player_position(Vector2 new_pos);
void battle_scene_render(void);

// ❌ Bad
void InitGame(void);
void UpdatePlayerPosition(Vector2 new_pos);
void BattleSceneRender(void);
```

## Variables

**Rule**: Use `snake_case` for all variable names

```c
// ✅ Good
float move_speed;
Vector2 player_position;
GameState current_state;

// ❌ Bad
float moveSpeed;
Vector2 playerPosition;
GameState currentState;
```

## Constants and Macros

**Rule**: Use `SCREAMING_SNAKE_CASE` for constants and macros

```c
// ✅ Good
#define MAX_HEALTH 100
#define WINDOW_WIDTH 1200
constexpr float DEFAULT_SPEED = 5.0f;

// ❌ Bad
#define maxHealth 100
#define windowWidth 1200
constexpr float defaultSpeed = 5.0f;
```

## Types (Structs, Enums, Typedefs)

**Rule**: Use `PascalCase` for type names to distinguish them from functions/variables

```c
// ✅ Good
typedef struct Player {
    Vector2 position;
    float base_speed;
} Player;

typedef enum GameState {
    FREE_ROAM,
    BATTLE_SCENE,
    PAUSED
} GameState;

// ❌ Bad
typedef struct player {
    Vector2 position;
    float baseSpeed;
} player;
```

## Struct/Union Members

**Rule**: Use `snake_case` for all struct and union members

```c
// ✅ Good
typedef struct BattleUI {
    Rectangle text_box;
    Vector2 player_mon_pos;
    Vector2 enemy_mon_pos;
} BattleUI;

// ❌ Bad
typedef struct BattleUI {
    Rectangle textBox;
    Vector2 playerMonPos;
    Vector2 enemyMonPos;
} BattleUI;
```

## Enum Values

**Rule**: Use `SCREAMING_SNAKE_CASE` for enum values, prefixed with the enum type

```c
// ✅ Good
typedef enum GameState {
    GAME_STATE_FREE_ROAM,
    GAME_STATE_BATTLE_SCENE,
    GAME_STATE_PAUSED
} GameState;

typedef enum MonTextureType {
    MON_TEXTURE_FRONT,
    MON_TEXTURE_BACK
} MonTextureType;

// ❌ Bad
typedef enum GameState {
    FREE_ROAM,
    BATTLE_SCENE,
    PAUSED
} GameState;
```

## File Names

**Rule**: Use `snake_case` for all file names

```c
// ✅ Good
battle_system.c
menu_renderer.h
player_controller.c

// ❌ Bad
BattleSystem.c
menuRenderer.h
playerController.c
```

## Function Prefixes

**Rule**: Use module/system prefixes for related functions

```c
// ✅ Good - Battle system functions
void battle_scene_init(void);
void battle_scene_update(void);
void battle_scene_render(void);
void battle_scene_cleanup(void);

// ✅ Good - Menu system functions
GridMenu* grid_menu_create(size_t items, size_t rows, size_t cols);
void grid_menu_destroy(GridMenu* menu);
void grid_menu_handle_input(GridMenu* menu);

// ❌ Bad - Inconsistent naming
void InitBattleScene(void);
void battle_update(void);
void renderBattle(void);
void EndBattleScene(void);
```

## Static/Private Functions

**Rule**: Prefix with underscore and module name for static functions

```c
// ✅ Good
static void _battle_calculate_damage(int attack, int defense);
static void _menu_update_positions(void);

// ❌ Bad
static void calculateDamage(int attack, int defense);
static void updatePositions(void);
```

## Global Variables

**Rule**: Use `snake_case` with `g_` prefix for globals (minimize usage)

```c
// ✅ Good (but avoid if possible)
Player g_player;
Camera2D g_camera;
Screen g_screen;

// ❌ Bad
Player player;
Camera2D camera;
Screen screen;
```

## Raylib Integration

**Note**: Since raylib uses PascalCase, we keep raylib function calls as-is but wrap them in our snake_case functions when appropriate:

```c
// ✅ Good - Keep raylib calls as-is
void render_player(Player* player) {
    DrawCircleV(player->position, player->size, RED);
}

// ✅ Good - Our wrapper functions use snake_case
void init_window(int width, int height, const char* title) {
    InitWindow(width, height, title);
}
```