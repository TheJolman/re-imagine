/*
* This is a package defintion for tmx: a tiled map renderer. It was briefly used in this project,
* but no longer. I'm keeping the package defintion here in case I ever go back to it.
*/
{
  lib,
  stdenv,
  cmake,
  fetchFromGitHub,
  zlib,
  libxml2,
}:
stdenv.mkDerivation rec {
  pname = "tmx";
  version = "1.10.0";
  src = fetchFromGitHub {
    owner = "baylej";
    repo = "tmx";
    rev = "11ffdcdc9bd65669f1a8dbd3a0362a324dda2e0c";
    sha256 = "sha256-RuQ3piUNLuCqXhf38QQzukeg/PcCVAAQmifym8fZ4vU=";
  };

  buildInputs = [
    zlib
    libxml2
  ];

  propagatedBuildInputs = [
    zlib
    libxml2
  ];

  nativeBuildInputs = [
    cmake
  ];

  cmakeFlags = [
    "-DWANT_ZLIB=ON"
    "-DWANT_ZSTD=OFF"
    "-DBUILD_SHARED_LIBS=OFF"
  ];

  meta = {
    homepage = "https://github.com/baylej/tmx";
    description = "C tmx map loader";
    changelog = "https://github.com/baylej/tmx/releases/tag/v${version}";
    license = lib.licenses.bsd2;
    maintainers = with lib.maintainers; [thejolman];
    platforms = lib.platforms.all;
  };
}
