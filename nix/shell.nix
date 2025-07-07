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
  pname,
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
    ]
    ++ lib.optional (!stdenv.hostPlatform.isDarwin) valgrind;

  CC = "gcc";
  CMAKE_GENERATOR = "Ninja";

  shellHook = ''
    alias ${pname}="./build/${pname}"
    echo "Dev shell activated."
  '';
}
