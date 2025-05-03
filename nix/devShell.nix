{
  pkgs,
  lib,
  system,
  self,
  pre-commit-hooks,
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
      clang
      gcc
      lldb
      gdb
      clang-tools
      valgrind # appears to be marked as broken on darwin
      raylib
      raylib-tileson
      gcc.cc.lib
    ];

    shellHook = ''
      ${self.checks.${system}.pre-commit-check.shellHook}
      export CC=clang
      export CMAKE_GENERATOR=Ninja
    '';
  };
}
