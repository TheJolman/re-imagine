{
  lib,
  stdenv,
  fetchFromGitHub,
  raylib,
  cmake,
  xorg,
}:
stdenv.mkDerivation (finalAttrs: {
  pname = "raylib-tileson";
  version = "4.2.0";
  src = fetchFromGitHub {
    owner = "RobLoach";
    repo = "raylib-tileson";
    rev = "3ad4416a4ced3ea9bbf7b6436ec0196b0d25b325";
    sha256 = "sha256-FSVal/bIF2y+xFM2WP4zYaRenqOYCE98K1A3XQQYk0k=";
  };

  nativeBuildInputs = [cmake];
  buildInputs = [
    raylib
    xorg.libXrandr
    xorg.libXinerama
    xorg.libXcursor
    xorg.libXi
  ];

  cmakeFlags = [
    "-DBUILD_RAYLIB_TILESON_EXAMPLE=OFF"
    "-DBUILD_TESTING=OFF"
    "-DCMAKE_CXX_STANDARD=17"
    "-DCMAKE_CXX_STANDARD_REQUIRED=ON"
    "-DCMAKE_CXX_EXTENSIONS=OFF"
  ];

  prePatch = ''
    rm -f cmake/Findraylib.cmake
  '';

  installPhase = ''
    runHook preInstall

    mkdir -p $out/include
    mkdir -p $out/lib
    cp $src/include/raylib-tileson.h $out/include/
    find . -name "librarylib-tileson.a" -exec cp {} $out/lib \;

    runHook postInstall
  '';

  meta = {
    homepage = "https://github.com/RobLoach/raylib-tileson";
    description = "Use Tiled maps in raylib, through Tileson.";
    changelog = "https://github.com/RobLoach/raylib-tileson/releases/tag/v${finalAttrs.version}";
    license = lib.licenses.bsd2;
    maintainers = with lib.maintainers; [];
    platforms = lib.platforms.all;
  };
})
