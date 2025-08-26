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
  glfw,
  lldb,
  mesa,
}:
mkShell {
  packages =
    [
      cmake
      pkg-config
      ninja
      gcc
      gdb
      lldb
      clang-tools
    ]
    ++ lib.optional (!stdenv.hostPlatform.isDarwin) valgrind;

  buildInputs = [
    raylib
    tmx
    glfw
    gcc.cc.lib
    mesa
  ];

  shellHook = ''
    export CC=gcc
    export CMAKE_GENERATOR=Ninja
    export CMAKE_BUILD_TYPE=Debug
  '';
}
