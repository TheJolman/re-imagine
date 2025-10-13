# CLAUDE.md

This file contains project-specific information for Claude Code to help with development tasks.

## Project Overview

RPG game built with raylib and C23.

### Build System

- **Build tool**: CMake with Ninja generator
- **Environment**: Nix flake-based development environment
- **Build/run commands**:
  ```bash
  nix develop --command cmake --build build
  nix develop --command ./build/rpg-raylib
  ```

### Development Environment

- Development shell and environment variables defined in `nix/shell.nix` for Unix systems
- Environment variables defined in `env.ps1` for Windows.
- Key dependencies: raylib 5.5
- Debug build by default (`CMAKE_BUILD_TYPE=Debug`)

### Project Structure

```
src/
├── main.c        # Entry point, window initialization
├── game.c        # Core game logic, InitGame(), UpdateGame(), DrawGame()
├── battle.c      # Battle system
├── map.c         # Map rendering system
├── pause.c       # Pause menu
├── mon.c         # Monster/Pokemon system
├── menu.c        # Menu system
└── utils.c       # Game dev utility functions

include/          # Header files
build/            # Build output
assets/           # Game assets
```

### Key Files

- **main.c**: Entry point with command line argument parsing and main game loop
- **game.c**: Contains `InitGame()`, `UpdateGame()`, `DrawGame()` functions
- **include/debug.h**: Contains `debug_log`. Useful for printf debugging

### Testing

- Use `lldb` for debugging (included in dev environment)
- `valgrind` available on non-Darwin systems
- `cmake --build build --target check` runs cppcheck
- No specific test framework currently configured

### Game Features

- State machine: FREE_ROAM, BATTLE_SCENE, PAUSED, TITLE_SCREEN
- 2D camera system with player following
- Basic movement with WASD + Shift for speed boost
- Battle scene with image rendering and UI for taking actions
- CSV based map renderer

### Memory Management

This game uses a linked list based memory allocator that wraps `malloc` and `free`.
- Use `heap_list.malloc` and `heap_list.free` instead of the equivalent functions from the
  standard library. They work they same way.
- `heap_list.free_all` frees all allocated memory and is registered with `atexit`.

### Code Style

- Style guidelines defined in `docs/naming-conventions.md`
- Use allman style braces.
- UI elements usually use a configuration struct to avoid excessive global state.
- This project uses C23.
    - Use `nullptr` over `NULL`.
- Prefer integral types from `<stdint.h>` as this project is cross-platform.

## Your Role

- If the user asks for clarification or an explanation about the project, do not modify any code.
- If the user asks you to modify the code (bug fix, feature request, etc.) make
  sure the project builds after you make your changes.
- Use read-only git commands at will. Only perform state-changing git commands upon request or
  after asking the user. Prefer rebasing over merging if pulling or updating a feature branch.
  - Make sure to run `cmake --build build --target format` before committing code.
- Code can only be contributed to main via github pull request. Only create a
  pull request if explicitly asked to submit code.
