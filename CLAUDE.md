# CLAUDE.md

This file contains project-specific information for Claude Code to help with development tasks.

## Project Overview

RPG game built with raylib and C. Uses TMX format for tilemaps.

## Build System

- **Build tool**: CMake with Ninja generator
- **Environment**: Nix flake-based development environment
- **Build commands**:
  ```bash
  nix develop --command bash -c "cd build && ninja"
  ```
- **Run**: `nix develop --command ./build/rpg-raylib`

## Development Environment

- Uses `direnv` for automatic environment loading
- Development shell defined in `flake.nix`
- Key dependencies: raylib, tmx, glfw, mesa
- Debug build by default (`CMAKE_BUILD_TYPE=Debug`)

## Project Structure

```
src/
├── main.c        # Entry point, window initialization
├── game.c        # Core game logic, InitGame(), UpdateGame(), DrawGame()
├── battle.c      # Battle system
├── map.c         # TMX map rendering
├── pause.c       # Pause menu
├── mon.c         # Monster/Pokemon system
├── menu.c        # Menu system
└── utils.c       # Utilities

include/          # Header files
build/           # Build output
assets/          # Game assets
```

## Key Files

- **main.c**: Entry point with command line argument parsing and main game loop
- **game.c**: Contains `InitGame()`, `UpdateGame()`, `DrawGame()` functions
- **Screen struct**: Defined in `include/map.h` - contains width/height for display

## Common Issues

- **Graphics initialization failures**: Window creation may fail on Wayland/EGL systems
- **Error handling**: Always check `IsWindowReady()` after `InitWindow()`
- **NixOS OpenGL**: Mesa package included for software rendering fallback

## Testing

- Use `lldb` for debugging (included in dev environment)
- `valgrind` available on non-Darwin systems
- No specific test framework currently configured

## Game Features

- State machine: FREE_ROAM, BATTLE_SCENE, PAUSED, TITLE_SCREEN
- 2D camera system with player following
- TMX tilemap support (currently commented out)
- Basic movement with WASD + Shift for speed boost