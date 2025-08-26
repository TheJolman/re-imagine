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
  llvmPackages_20,
  cppcheck,
}:
mkShellNoCC {
  packages =
    [
      cmake
      pkg-config
      ninja
      llvmPackages_20.clangUseLLVM
      gdb
      lldb
      llvmPackages_20.clang-tools
      cppcheck
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
