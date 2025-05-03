{
  lib,
  stdenv,
  cmake,
  fetchFromGithub,
}:
stdenv.mkDerivation (finalAttrs: {
  pname = "tileson";
  version = "v1.4.0";
  src = fetchFromGithub {
    owner = "SSBMTonberry";
    repo = "tileson";
    rev = "ccc4a3d906fc6547141d4186cb99c8dace562f65";
    sha256 = "";
  };

  nativeBuildInputs = [
    cmake
  ];

  meta = {
    homepage = "https://github.com/SSBMTonberry/tileson";
    description = "A modern and helpful cross-platform json-parser for C++, used for parsing Tiled maps. ";
    changelog = "https://github.com/SSBMTonberry/tileson/releases/tag/v${finalAttrs.version}";
    license = lib.licenses.bsd2;
    maintainers = with lib.maintainers; [];
    platforms = lib.platforms.all;
  };
})
