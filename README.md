# Raylib Game Project

A cross-platform game using Raylib, CMake, and Nix.

## Quick Start - Linux/MacOS

1. Install Nix (if you haven't already):
```bash

curl --proto '=https' --tlsv1.2 -sSf -L https://install.determinate.systems/nix | \
  sh -s -- install
```

2. Install [direnv](https://direnv.net/) (optional but recommended)
* direnv can be obtained from various [package managers](https://direnv.net/docs/installation.html).
```bash
# For Debian/Ubuntu
sudo apt-get install direnv

# For macOS
brew install direnv
```
* Hook direnv into your shell
```bash
# For bash users (put in ~/.bashrc)
eval "$(direnv hook bash)"

# For zsh users (put in ~/.zshrc)
eval "$(direnv hook zsh)"
```
* You will need to restart your shell or `source` your shell rc file

3. Clone and enter the project:
```bash
git clone https://github.com/TheJolman/raylib-game.git
cd raylib-game
```

4. Start developing:
```bash
# If you have direnv, run this once:
direnv allow
# Whenever you cd into the directory all dependencies will now be loaded automatically

# If you don't have direnv you will need to run this each time:
nix develop
```

5. Build and run:
```bash
# First time setup only (or when CMakeLists.txt changes)
cmake -B build
# Build project
cmake --build build
# Run
./build/raylib-game
```

### Developing Without Nix

This can be run without installing Nix, but you will need to download and compile raylib 5.5 and obtain all other dependencies (`cmake`, `ninja`, C compiler) yourself.

## Quick Start - Windows

1. Install `gcc`, `g++`, `cmake`, and `ninja`. I recommend using [Chocolatey](https://chocolatey.org/)

Install Chocolately (if you haven't already):
```ps1
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
```
Restart your shell and install the dependencies:
```ps1
choco install mingw cmake ninja
```

2. Clone and enter the project:
```ps1
git clone https://github.com/TheJolman/raylib-game.git
cd raylib-game
```

3. Build and run:  
*Note: The initial build on Windows will likely take a few minutes as CMake downloads and compiles Raylib from source.
Subsequent builds will be much faster.*
```ps1
# First time setup only (or when CMakeLists.txt changes)
cmake -B build -G Ninja
# Build project
cmake --build build
# Run project
.\build\raylib-game
```

