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
        pname = "rpg-raylib";
      in {
        packages.default = pkgs.callPackage ./nix/default.nix {
          tmx = pkgs.callPackage ./nix/tmx.nix {};
        };
        devShells.default = pkgs.callPackage ./nix/shell.nix {
          tmx = pkgs.callPackage ./nix/tmx.nix {};
        };
      }
    );
}
