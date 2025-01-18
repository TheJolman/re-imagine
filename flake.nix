{
  description = "Generic Dev Environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils,
  }:
    flake-utils.lib.eachDefaultSystem (
      system: let
        pkgs = nixpkgs.legacyPackages.${system};
      in {
        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            cmake
            clang
            clang-tools
            # valgrind  # appears to be marked as broken on darwin
            raylib
          ];

          shellHook = ''
            export CC=clang
            export CXX=clang++
          '';
        };
      }
    );
}
