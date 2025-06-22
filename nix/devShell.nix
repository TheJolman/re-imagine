{
  mkShell,
  lib,
  stdenv,
  pre-commit-hooks,
  cmake,
  pkg-config,
  ninja,
  gcc,
  gdb,
  clang-tools,
  raylib,
  tmx,
  valgrind,
}: rec {
  pre-commit-check = pre-commit-hooks {
    src = ../src;
    hooks = {
      clang-format = {
        enable = true;
        types_or = lib.mkForce ["c"];
      };
      clang-tidy = {
        enable = true;
        types_or = lib.mkForce ["c"];
      };
    };
  };

  default = mkShell {
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

    shellHook = ''
      ${pre-commit-check.shellHook}
      export CC=gcc
      export CMAKE_GENERATOR=Ninja
    '';
  };
}
