{
  stdenv,
  cmake,
  ninja,
  raylib,
  tmx,
}:
stdenv.mkDerivation {
  name = "rpg-raylib";
  version = "0.1.0";
  src = ../.;

  nativeBuildInputs = [
    cmake
    ninja
  ];

  buildInputs = [
    raylib
    tmx
  ];

  cmakeFlags = [
    "-DCMAKE_BUILD_TYPE=Release"
    "-G Ninja"
  ];

  # installPhase = ''
  #   mkdir -p $out/bin
  #   cp raylib-game $out/bin/
  # '';
}
