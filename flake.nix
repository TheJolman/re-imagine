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

        # raylib-tileson = import ./nix/raylib-tileson.nix {inherit pkgs;};
        # tileson = import ./nix/tileson.nix {
        tmx = import ./nix/tmx.nix {
          inherit
            (pkgs)
            lib
            stdenv
            cmake
            fetchFromGitHub
            zlib
            libxml2
            ;
        };
        packages = import ./nix/packages.nix {
          inherit pkgs;
          src = ./.;
        };
        devModules = import ./nix/devShell.nix {
          inherit pkgs lib system self pre-commit-hooks tmx;
        };
      in {
        packages = packages;
        checks = devModules.checks;
        devShells = {
          default = devModules.default;
        };
      }
    );
}
