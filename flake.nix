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

        raylib-tileson = import ./nix/raylib-tileson.nix
      in {
        packages.default = pkgs.stdenv.mkDerivation {
          pname = "raylib-game";
          version = "0.1.0";

          src = ./.;

          nativeBuildInputs = with pkgs; [
            cmake
            ninja
          ];

          buildInputs = with pkgs; [
            raylib
          ];

          cmakeFlags = [
            "-DCMAKE_BUILD_TYPE=Release"
            "-G Ninja"
            "-DCMAKE_CXX_STANDARD=17"
            "-DCMAKE_CXX_STANDARD_REQUIRED=ON"
            "-DCMAKE_CXX_EXTENSIONS=OFF"
          ];

          installPhase = ''
            mkdir -p $out/bin
            cp raylib-game $out/bin/
          '';
        };

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
            export PKG_CONFIG_PATH="${raylib-tileson}/lib/pkgconfig:$PKG_CONFIG_PATH"

            export RAYLIB_TILESON_INCLUDE="${raylib-tileson}/include"
            export RAYLIB_TILESON_LIB="${raylib-tileson}/lib"
          '';
        };
      }
    );
}
