## Project Overview

RPG game built with raylib and C23.

### Build System

- **Build tool**: CMake with Ninja generator
- **Environment**: Nix flake-based development environment
- **Build/run commands**:
  ```bash
  nix develop --command cmake --build build
  nix develop --command ./build/re-imagine
  ```

### Development Environment

- Development environment variables defined in `.env`. Nothing sensitive here, version-controlled.
