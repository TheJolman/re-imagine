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

        raylib-tileson = pkgs.stdenv.mkDerivation {
          pname = "raylib-tileson";
          version = "4.2.0";
          src = pkgs.fetchFromGitHub {
            owner = "RobLoach";
            repo = "raylib-tileson";
            rev = "3ad4416a4ced3ea9bbf7b6436ec0196b0d25b325";
            sha256 = "sha256-FSVal/bIF2y+xFM2WP4zYaRenqOYCE98K1A3XQQYk0k=";
          };

          nativeBuildInputs = with pkgs; [
            cmake
            ninja
            pkg-config
            pkgconf
          ];

          buildInputs = with pkgs; [
            raylib
          ];

          cmakeFlags = [
            "-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=lib"
            "-DBUILD_RAYLIB_TILESON_EXAMPLE=OFF"
            "-DBUILD_TESTING=OFF"
            "-DUSE_SYSTEM_RAYLIB=ON"
            "-DCMAKE_PREFIX_PATH=${pkgs.raylib}"
            "-DCMAKE_CXX_STANDARD=17"
            "-DCMAKE_CXX_STANDARD_REQUIRED=ON"
            "-DCMAKE_CXX_EXTENSIONS=OFF"
          ];

          # Patch CMakeLists.txt and source files
          prePatch = ''
            rm -f cmake/Findraylib.cmake
          '';

          installPhase = ''
            mkdir -p $out/{lib,include}
            find . -name "libraylib-tileson.a" -exec cp {} $out/lib/ \;
            cp ../include/raylib-tileson.h $out/include/
            cp ../src/tileson.hpp $out/include/

            mkdir -p $out/lib/pkgconfig
            cat > $out/lib/pkgconfig/raylib-tileson.pc << EOF
            prefix=$out
            exec_prefix=\''${prefix}
            libdir=\''${exec_prefix}/lib
            includedir=\''${prefix}/include

            Name: raylib-tileson
            Description: Tileson wrapper for raylib
            Libs: -L\''${libdir} -lraylib-tileson
            Cflags: -I\''${includedir}
            EOF
          '';
        };
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
