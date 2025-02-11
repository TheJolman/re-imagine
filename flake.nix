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
        pkgs = nixpkgs.legacyPackages.${system};
        supportedSystems = ["x86_64-linux" "aarch64-linux" "x86_64-darwin" "aarch64-darwin"];
        forAllSystems = nixpkgs.lib.genAttrs supportedSystems;
      in {
        checks = forAllSystems (system: {
          pre-commit-check = pre-commit-hooks.lib.${system}.run {
            src = ./src;
            hooks = {
              clang-format.enable = true;
              clang-tidy.enable = true;
            };
          };
        });
        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            cmake
            ninja
            clang
            lldb
            gdb
            clang-tools
            cppcheck
            valgrind # appears to be marked as broken on darwin
            raylib
          ];

          shellHook = ''
            export CC=clang
            export CMAKE_GENERATOR=Ninja
          '';
        };
      }
    );
}
