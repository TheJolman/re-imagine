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
      in {
        packages.default = pkgs.callPackage ./nix/package.nix {
          tmx = pkgs.callPackage ./nix/package.nix {};
        };
        devShells.default = pkgs.callPackage ./nix/devShell.nix {
          tmx = pkgs.callPackage ./nix/package.nix {};
          pre-commit-hooks = pre-commit-hooks.lib.${system}.run;
        };
      }
    );
}
