# Raylib Game Project

A cross-platform game developed with Raylib, C11, and CMake.  
This game is being developed as a part of VGDC @ CSUF.  
  
Idea: Pokemon-like top down rpg with a small story.  

## Requirements

- C23 compiler
- CMake + Ninja
- Raylib 5.5 (optional, CMake will download and compile this for you if you don't have it)

## Quick Start - Windows
1. Install `clang`, `cmake`, and `ninja`. I recommend using [Chocolatey](https://chocolatey.org/) or [Scoop](https://scoop.sh/):
```sh
# Chocolatey (use admin shell)
choco install -y llvm cmake ninja

# Scoop
scoop install llvm cmake ninja
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
cmake --build build
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

# If you don't have direnv, run this each time you enter the directory:
nix develop
```

4. Setup build files:
```
cmake -B build
```

4. Build and run:
```sh
cmake --build build
./build/raylib-game
```

### Unix without Nix
You of course do not need to use the nix dev shell, but it is recommended. As long as you
have CMake, Ninja, and a C23 compiler you should be able to compile and run this project.
