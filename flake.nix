{
  description = "OpenGL bindings for Lean";

  inputs = {
    lean = {
      url = github:leanprover/lean4;
    };
    nixpkgs.url = github:nixos/nixpkgs;
    flake-utils = {
      url = github:numtide/flake-utils;
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };

  outputs = { self, lean, flake-utils, nixpkgs }:
    let
      supportedSystems = [
        # "aarch64-linux"
        # "aarch64-darwin"
        "i686-linux"
        "x86_64-darwin"
        "x86_64-linux"
      ];
    in
    flake-utils.lib.eachSystem supportedSystems (system:
      let
        leanPkgs = lean.packages.${system};
        pkgs = nixpkgs.legacyPackages.${system};
        lib = nixpkgs.lib // (import ./nix/lib.nix { inherit (nixpkgs) lib; });
        inherit (lib) concatStringsSep makeOverridable;
        buildCLib = import ./nix/buildCLib.nix { inherit nixpkgs system lib; };
        includes = [
          "${pkgs.libglvnd.dev}/include"
          "${leanPkgs.lean-bin-tools-unwrapped}/include"
        ];
        INCLUDE_PATH = concatStringsSep ":" includes;
        hasPrefix =
          # Prefix to check for
          prefix:
          # Input string
          content:
          let
            lenPrefix = builtins.stringLength prefix;
          in
          prefix == builtins.substring 0 lenPrefix content;
        libOpenGL = pkgs.libglvnd.out // {
          name = "lib/libSDL2.so";
          linkName = "OpenGL";
          libName = "lib/libOpenGL.so";
          # __toString = d: "${pkgs.SDL2.out}/lib";
        };
        sharedLibDeps = [ libOpenGL ];
        linkName = "lean-opengl-bindings";
        c-shim = buildCLib {
          updateCCOptions = d: d ++ (map (i: "-I${i}") includes);
          name = linkName;
          sourceFiles = [ "bindings/*.c" ];
          src = builtins.filterSource
            (path: type: hasPrefix (toString ./. + "/bindings") path) ./.;
          extraDrvArgs = {
            inherit linkName;
          };
        };
        c-shim-debug = c-shim.override {
          debug = true;
          updateCCOptions = d: d ++ (map (i: "-I${i}") includes) ++ [ "-O0" ];
        };
        name = "OpenGL";  # must match the name of the top-level .lean file
        project = makeOverridable leanPkgs.buildLeanPackage
          {
            inherit name;
            linkFlags = [ "-L${pkgs.libglvnd.out}/lib" "-lOpenGL" "-lGL" "-lGLESv2" ];
            # Where the lean files are located
            nativeSharedLibs = sharedLibDeps ++ [ c-shim ];
            src = ./src;
          };
        test = makeOverridable leanPkgs.buildLeanPackage
          {
            name = "Tests";
            deps = [ project ];
            # Where the lean files are located
            src = ./test;
          };
        joinDepsDerivationns = getSubDrv:
          pkgs.lib.concatStringsSep ":" (map (d: "${getSubDrv d}") ([ ] ++ project.allExternalDeps));
        withGdb = bin: pkgs.writeShellScriptBin "${bin.name}-with-gdb" "${pkgs.gdb}/bin/gdb ${bin}/bin/${bin.name}";
      in
      {
        inherit project test;
        packages = {
          ${name} = project.sharedLib;
          test = test.executable;
          debug-test = (test.overrideArgs {
            debug = true;
            deps =
            [ (project.override {
                nativeSharedLibs = sharedLibDeps ++ [ c-shim-debug ];
              })
            ];
          }).executable // { allowSubstitutes = false; };
          gdb-test = withGdb self.packages.${system}.debug-test;
        };

        checks.test = test.executable;

        defaultPackage = self.packages.${system}.${name};
        devShell = pkgs.mkShell {
          inputsFrom = [ project ];
          buildInputs = with pkgs; [
            leanPkgs.lean
          ];
          LEAN_PATH = joinDepsDerivationns (d: d.modRoot);
          LEAN_SRC_PATH = joinDepsDerivationns (d: d.src);
          C_INCLUDE_PATH = INCLUDE_PATH;
          CPLUS_INCLUDE_PATH = INCLUDE_PATH;
        };
      });
}
