# Contributing Guide

Thank you for your interest in contributing to RPG Raylib! This document outlines the development process and standards for this project.

## Development Setup
See [`README.md`](./../README.md) for details on setting up the project.

## Development Workflow

### Making Changes
1. Create a feature branch from `main`:
   ```sh
   git switch main
   git pull --rebase
   git switch -c your-feature-name
   ```

2. Make your changes following the [coding standards](#coding-standards)

3. Format your code before committing:
   ```sh
   cmake --build build --target format
   ```

4. Run static analysis:
   ```sh
   cmake --build build --target check
   ```

5. Test your changes by building and running the game:
   ```sh
   cmake --build build
   ./build/re-imagine
   .\build\re-imagine  # Windows
   ```

### Submitting Changes
1. **All code changes must go through GitHub pull requests** - direct pushes to `main` are not allowed

2. Ensure your branch is up to date with `main` and push:
   ```sh
   git fetch origin
   git rebase origin/main
   git push -u origin your-feature-name
   ```

3. Create a pull request with:
   - Clear description of changes
   - Reference to any related issues
   - Screenshots/videos for visual changes

4. Ensure all CI checks pass before requesting review

## Coding Standards

This project follows specific naming conventions and code style. Please review [`docs/naming-conventions.md`](./naming-conventions.md) for detailed guidelines.

### Key Points
- **Functions and variables**: `snake_case`
- **Types (structs, enums)**: `PascalCase`
- **Constants and macros**: `SCREAMING_SNAKE_CASE`
- **Files**: `snake_case.c` / `snake_case.h`
- **Module prefixes**: Use consistent prefixes for related functions (e.g., `battle_scene_*`, `grid_menu_*`)

### Code Quality
- Write clear, descriptive function and variable names
- Add comments for complex logic, not obvious code
- Use `debug_log()` from `include/debug.h` for debugging output
- Follow the existing project structure in `src/` and `include/`
- Try to document public functions and types with doxygen comments. See
  [`doxygen.md`](./doxygen.md) for details.

## Project Architecture

### Core Files
- `src/main.c` - Entry point and main game loop
- `src/game.c` - Core game logic (`InitGame()`, `UpdateGame()`, `DrawGame()`)
- `src/battle.c` - Battle system implementation
- `src/map.c` - Map rendering system
- `src/pause.c` - Pause menu functionality
- `src/mon.c` - Monster/Pokemon system
- `src/menu.c` - UI menu system
- `src/utils.c` - Utility functions

### Game States
The game uses a state machine with these states:
- `FREE_ROAM` - Player exploration
- `BATTLE_SCENE` - Combat encounters
- `PAUSED` - Pause menu
- `TITLE_SCREEN` - Main menu

## Debugging and Testing

### Debugging Tools
- Use `lldb` or `gdb` for debugging (included in Nix environment)
- `valgrind` available on Linux systems
- `debug_log()` function for printf-style debugging

### Running Checks
- Static analysis: `cmake --build build --target check`
- Code formatting: `cmake --build build --target format`

## Versioning and Releases

To release a version, use git tags:
```sh
git tag -a v0.1.0 -m "initial version"
git push origin v0.1.0
```

## Getting Help

- Check existing [GitHub issues](https://github.com/TheJolman/re-imagine/issues)
- Review project documentation in `docs/`
- Look at `CLAUDE.md` for AI assistant context

## Additional Resources

- [Raylib Documentation](https://www.raylib.com/)
- [C23 Standard](https://en.cppreference.com/w/c)
- [CMake Documentation](https://cmake.org/documentation/)
