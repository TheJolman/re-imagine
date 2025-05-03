{pkgs}: let
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
  package = raylib-tileson;
  setupEnv = ''
    export PKG_CONFIG_PATH="${raylib-tileson}/lib/pkgconfig:$PKG_CONFIG_PATH"
    export RAYLIB_TILESON_INCLUDE="${raylib-tileson}/include"
    export RAYLIB_TILESON_LIB="${raylib-tileson}/lib"
  '';
}
