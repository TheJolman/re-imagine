{
  mkShellNoCC,
  lib,
  stdenv,
  cmake,
  pkg-config,
  ninja,
  gdb,
  raylib,
  valgrind,
  lldb,
  llvmPackages_21,
}:
mkShellNoCC {
  packages =
    [
      cmake
      pkg-config
      ninja
      llvmPackages_21.clangUseLLVM
      gdb
      lldb
      llvmPackages_21.clang-tools
    ]
    ++ lib.optional (!stdenv.hostPlatform.isDarwin) valgrind;

  buildInputs = [
    raylib
  ];

  shellHook = ''
    export CC=clang
    export CMAKE_GENERATOR=Ninja
    export CMAKE_BUILD_TYPE=Debug
  '';
}
