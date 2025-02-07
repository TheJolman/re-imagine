# Raylib Game Project

A cross-platform game developed with Raylib, plain C, and CMake.  
This game is being developed as a part of VGDC @ CSUF.  
  
Idea: Pokemon-like top down rpg with a small story.  

## Requirements

- C compiler (GCC recommended)
- CMake
- Ninja build system (recommended) or Make

## Quick Start - Windows

### Using Visual Studio 2022

This should work perfectly with Visual Studio 2022. Just ensure you have "Desktop development with C++" installed.
1. Clone repo:
```ps1
git clone https://github.com/TheJolman/raylib-game.git
```
2. Open in VS 2022 and wait for CMake to install/compile raylib
3. Run

### Using MinGW

1. Install `mingw`, `cmake`, and `ninja`. I recommend using [Chocolatey](https://chocolatey.org/) or [Scoop](https://scoop.sh/):
```ps1
# Chocolatey (use admin shell)
choco install -y mingw-w64 cmake ninja

# Scoop
scoop install gcc cmake ninja
```

2. Clone and enter the project:
```ps1
git clone https://github.com/TheJolman/raylib-game.git
cd raylib-game
```

3. Build and run:  
*Note: The initial build will likely take a few minutes as CMake downloads and compiles Raylib from source.
Subsequent builds will be much faster.*
```ps1
# First time setup only (or when CMakeLists.txt changes)
cmake -B build -G Ninja
# Build
cmake --build build
# Run
.\build\raylib-game
```

## Quick Start - Linux/MacOS

1. install `CMake`, `Ninja`, and a C compiler (preferably gcc for consistency):
```bash
# macOS
brew install cmake ninja gcc

# Ubuntu / Debian-based
sudo apt-get install cmake ninja-build gcc

# Fedora
sudo dnf install cmake ninja-build gcc
```

2. Clone and enter the project:
```bash
git clone https://github.com/TheJolman/raylib-game.git
cd raylib-game
```

3. Build and run:  
*Note: The initial build will likely take a few minutes as CMake downloads and compiles Raylib from source.
Subsequent builds will be much faster.*
```bash
# First time setup only (or when CMakeLists.txt changes)
cmake -B build -G Ninja
# Build
cmake --build build
# Run
./build/raylib-game
```

### Nix

Alternatively, you can use the Nix dev shell (this will prevent you from having to compile raylib from source):

1. Install Nix and direnv (optional) if you haven't already:
https://determinate.systems/nix-installer/  
https://direnv.net/docs/installation.html  

2. Clone and enter the project:
```bash
git clone https://github.com/TheJolman/raylib-game.git
cd raylib-game
```

3. Start developing:
```bash
# If you have direnv, run this once:
direnv allow

# If you don't have direnv you will need to run this each time:
nix develop
```

4. Build and run:
```bash
# First time setup only (or when CMakeLists.txt changes)
cmake -B build
# Build
cmake --build build
# Run
./build/raylib-game
```
