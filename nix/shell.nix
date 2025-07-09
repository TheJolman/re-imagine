{
  mkShell,
  lib,
  stdenv,
  cmake,
  pkg-config,
  ninja,
  gcc,
  gdb,
  clang-tools,
  raylib,
  tmx,
  valgrind,
  glfw
}:
mkShell {
  packages =
    [
      cmake
      pkg-config
      ninja
      gcc
      gdb
      clang-tools
      raylib
      tmx
      gcc.cc.lib
      glfw
    ]
    ++ lib.optional (!stdenv.hostPlatform.isDarwin) valgrind;

  CC = "gcc";
  CMAKE_GENERATOR = "Ninja";

  shellHook = ''
    export PATH="$PWD/build:$PATH"
    echo "Dev shell activated."
  '';
}
