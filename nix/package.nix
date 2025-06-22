{
  mkDerivation,
  cmake,
  ninja,
  raylib,
}:
mkDerivation {
  pname = "raylib-game";
  version = "0.1.0";
  src = ../.;

  nativeBuildInputs = [
    cmake
    ninja
  ];

  buildInputs = [
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
}
