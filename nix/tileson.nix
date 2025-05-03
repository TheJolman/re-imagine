{
  lib,
  stdenv,
  cmake,
  fetchFromGitHub,
}:
stdenv.mkDerivation (finalAttrs: {
  pname = "tileson";
  version = "1.4.0";
  src = fetchFromGitHub {
    owner = "SSBMTonberry";
    repo = "tileson";
    rev = "ccc4a3d906fc6547141d4186cb99c8dace562f65";
    sha256 = "sha256-PiH8QSGZwYUbH0FYP/y13HtDV0dohpVGeW+9w5TEK5U=";
  };

  nativeBuildInputs = [
    cmake
  ];

  cmakeFlags = [
    "-DBUILD_TESTS=OFF"
    "-DBUILD_EXAMPLES=OFF"
  ];

  installPhase = ''
    runHook preInstall

    mkdir -p $out/include/tileson
    if [ -d include ]; then
      find include -mindepth 1 -exec cp -r -t $out/include/tileson/ {} +
    fi

    if [ -f TilesonConfig.h ]; then
      cp TilesonConfig.h $out/include/tileson/
    fi

    runHook postInstall
  '';

  meta = {
    homepage = "https://github.com/SSBMTonberry/tileson";
    description = "A modern and helpful cross-platform json-parser for C++, used for parsing Tiled maps. ";
    changelog = "https://github.com/SSBMTonberry/tileson/releases/tag/v${finalAttrs.version}";
    license = lib.licenses.bsd2;
    maintainers = with lib.maintainers; [];
    platforms = lib.platforms.all;
  };
})
