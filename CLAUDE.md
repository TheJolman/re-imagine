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
- Key dependencies: raylib
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
- CSV based map renderer (WIP)

## Your Role
- If the user asks for clarification or an explanation about the project, do not modify any code.
- If the user asks you to modify the code (bug fix, feature request, etc.) make
  sure the project builds after you make your changes.
- You have access to `git` and `gh` commands. Use them to look at the log, issues, make
  commits, switch branches, create worktrees, etc. Prefer rebasing over merging if pulling or
  updating a feature branch. Only perform state-changing git commands upon request or after
  asking the user. You can use read-only git commands without asking.
- Code can only be contributed to main via github pull request. Only create a
  pull request if explicitly asked to submit code.
