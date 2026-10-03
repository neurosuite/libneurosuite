{
  description = "libneurosuite: shared library for Klusters, NeuroScope and NDManager";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }:
    let
      systems = [ "x86_64-linux" "aarch64-linux" "aarch64-darwin" ];
      forAllSystems = f: nixpkgs.lib.genAttrs systems (system: f nixpkgs.legacyPackages.${system});
    in
    {
      packages = forAllSystems (pkgs: rec {
        libneurosuite = pkgs.qt6Packages.callPackage ./nix/package.nix { src = self; };
        libneurosuite-nowebengine = libneurosuite.override { withWebEngine = false; };
        default = libneurosuite;
      });

      devShells = forAllSystems (pkgs: {
        default = pkgs.mkShell {
          inputsFrom = [ self.packages.${pkgs.stdenv.hostPlatform.system}.default ];
          packages = [ pkgs.clang-tools ];
        };
      });
    };
}
