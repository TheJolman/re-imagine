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
            valgrind
            raylib
            # ninja
            # xorg.libX11
            # xorg.libXrandr
            # xorg.libXi
            # xorg.libXcursor
            # xorg.libXinerama
            # libGL
            # libGLU
            # alsa-lib
          ];

          shellHook = ''
            export CC=clang
            export CXX=clang++
          '';
        };
      }
    );
}
