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
        tmx = pkgs.callPackage ./nix/tmx.nix;
      in {
        packages.default = pkgs.callPackage ./nix/package.nix {};
        devShells.default =
          (pkgs.callPackage ./nix/devShell.nix {
            tmx = tmx;
          }).default;
        checks =
          (pkgs.callPackage ./nix/devShell.nix {
            pre-commit-hooks = pre-commit-hooks.${system}.run;
          }).checks;
      }
    );
}
