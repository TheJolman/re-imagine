{
  pkgs,
  src,
}: {
  default = pkgs.stdenv.mkDerivation {
    pname = "raylib-game";
    version = "0.1.0";

    inherit src;

    nativeBuildInputs = with pkgs; [
      cmake
      ninja
    ];

    buildInputs = with pkgs; [
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
  };
}
