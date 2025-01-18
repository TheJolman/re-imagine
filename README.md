# Raylib Game Project

A cross-platform game using Raylib, CMake, and Nix.

## Quick Start (Linux/macOS)

1. Install Nix (if you haven't already):
```bash

curl --proto '=https' --tlsv1.2 -sSf -L https://install.determinate.systems/nix | \
  sh -s -- install
```

2. Install [direnv](https://direnv.net/) (optional but recommended)
* direnv can be obtained from various [package managers](https://direnv.net/docs/installation.html).
```bash
# for Debian/Ubuntu
sudo apt-get install direnv

# for macOS
brew install direnv
```
* hook direnv into your shell
```bash
# for bash users
eval "$(direnv hook bash)"

# for zsh users
eval "$(direnv hook zsh)"
```
* Restart your shell or `source` your shell rc file

3. Clone and enter the project:
```bash
git clone https://github.com/TheJolman/raylib-game.git
cd raylib-game
```

4. Start developing:
```bash
# If you have direnv:
direnv allow
# then whenever you cd into the directory, all dependencies
# will be loaded automatically

# If you don't have direnv:
nix develop
```

5. Build and run:
```bash
cmake -B build
cmake --build build
./build/raylib-game
```

## Without Nix

This can be run without installing Nix, but you will need to download and compile raylib 5.5 along with any other dependencies yourself.

## For Windows Users

Try using Visual Studio. If not, make sure you have `clang` (or an equivalent C/C++ compiler) installed and `raylib` should automatically install and compile when you run CMake for the first time.
