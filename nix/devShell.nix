{
  pkgs,
  lib,
  system,
  self,
  pre-commit-hooks,
  tmx,
  raylib-tileson,
}: {
  checks = {
    pre-commit-check = pre-commit-hooks.lib.${system}.run {
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
  };

  default = pkgs.mkShell {
    packages = with pkgs; [
      cmake
      pkg-config
      ninja
      gcc
      gdb
      clang-tools
      gcc.cc.lib
      raylib
      tmx
      raylib-tileson
    ] ++ lib.optional (!stdenv.isDarwin) valgrind;

    shellHook = ''
      ${self.checks.${system}.pre-commit-check.shellHook}
      export CC=gcc
      export CMAKE_CXX_COMPILER=g++
      export CMAKE_GENERATOR=Ninja
    '';
  };
}
