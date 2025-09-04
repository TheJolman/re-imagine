# Raylib Game Project

A cross-platform game developed with Raylib, C23, and CMake.  
This game is being developed with VGDC@CSUF.  
  
Pitch: Pokemon-like top down rpg with a small story.  

## Requirements

- Recent version of Clang
- CMake + Ninja
- Raylib 5.5 (optional, CMake will download and compile this for you if you don't have it)

## Quick Start - Windows
1. Install `clang`, `cmake`, and `ninja` using one of the following package managers (if you don't know which to use, use WinGet):
```sh
# WinGet
winget install BrechtSanders.WinLibs.POSIX.UCRT.LLVM

# Chocolatey (admin shell)
choco install -y llvm cmake ninja

# Scoop
scoop install llvm cmake ninja
```

2. Clone and enter the project:
```
git clone https://github.com/TheJolman/raylib-game.git
cd raylib-game
```

3. Load the required environment variables (requires Powershell):
```
. .\env.ps1
```

3. Setup build files:
> This might take a few minutes as CMake downloads and compiles the project's dependencies from
> source. You only need to run this before your first build and when `CMakeLists.txt` changes.
```sh
cmake -B build
```

3. Build and run:
```sh
cmake --build build
.\build\raylib-game
```

## Quick Start - Linux/MacOS

1. Install [Nix](https://determinate.systems/nix-installer/) and optionally [direnv](https://direnv.net/docs/installation.html).

2. Clone and enter the project:
```
git clone https://github.com/TheJolman/raylib-game.git
cd raylib-game
```

3. Enter dev shell:
```sh
# If you have direnv, run this once:
direnv allow

# If you don't have direnv, run this each time you enter the directory:
nix develop
```

4. Setup build files:
> You only need to run this before your first build and when `CMakeLists.txt` changes.
```
cmake -B build
```

4. Build and run:
```sh
cmake --build build
./build/raylib-game
```
