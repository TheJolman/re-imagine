# Raylib Game Project

A cross-platform game developed with Raylib, C11, and CMake.  
This game is being developed as a part of VGDC @ CSUF.  
  
Idea: Pokemon-like top down rpg with a small story.  

## Requirements

- C11 compiler
- CMake + Ninja
- Raylib 5.5 (optional, CMake will download and compile this for you if you don't have it)

## Quick Start - Windows
You can either use Visual Studio (CLion probably works just as well, haven't tested), or MinGW
with whatever editor you prefer. Both options are listed here:

### Using Visual Studio 2022

This should work perfectly with Visual Studio 2022. Just ensure you have "Desktop development with C++" installed.
1. Clone repo:
```
git clone https://github.com/TheJolman/raylib-game.git
```
2. Open in VS 2022 and wait for CMake to install and compile raylib
3. Run

### Using MinGW

1. Install `mingw`, `cmake`, and `ninja`. I recommend using [Chocolatey](https://chocolatey.org/) or [Scoop](https://scoop.sh/):
```sh
# Chocolatey (use admin shell)
choco install -y mingw-w64 cmake ninja

# Scoop
scoop install gcc cmake ninja
```

2. Clone and enter the project:
```
git clone https://github.com/TheJolman/raylib-game.git
cd raylib-game
```

3. Setup build files:
> This might take a few minutes as CMake downloads and compiles the project's dependencies from
> source.
```sh
# First time setup only (or when CMakeLists.txt changes)
cmake -B build -G Ninja
```

3. Build and run:
```sh
# Build
cmake --build build
# Run
.\build\raylib-game
```

## Quick Start - Linux/MacOS

1. Install Nix and optionally direnv:
https://determinate.systems/nix-installer/  
https://direnv.net/docs/installation.html  

2. Clone and enter the project:
```
git clone https://github.com/TheJolman/raylib-game.git
cd raylib-game
```

3. Enter dev shell:
```sh
# If you have direnv, run this once:
direnv allow

# If you don't have direnv you will need to run this each time:
nix develop
```

4. Setup build files:
```
cmake -B build
```

4. Build and run:
```sh
# Build
cmake --build build
# Run
./build/raylib-game
```

### Alternative Setups
You of course do not need to use the nix dev shell, but it is recommended. As long as you
have CMake, Ninja, and a C11 compiler you should be able to compile and run this without issue.
