{
  description = "Generic Dev Environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
    pre-commit-hooks.url = "github:cachix/git-hooks.nix";
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils,
    pre-commit-hooks,
  }:
    flake-utils.lib.eachDefaultSystem (
      system: let
        lib = nixpkgs.lib;
        pkgs = nixpkgs.legacyPackages.${system};
      in {
        checks = {
          pre-commit-check = pre-commit-hooks.lib.${system}.run {
            src = ./src;
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

        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            cmake
            ninja
            clang
            lldb
            gdb
            clang-tools
            valgrind # appears to be marked as broken on darwin
            raylib
          ];

          shellHook = ''
            ${self.checks.${system}.pre-commit-check.shellHook}
            export CC=clang
            export CMAKE_GENERATOR=Ninja
          '';
        };
      }
    );
}
