cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_COMPILER g++)
project(raylib-game C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(SOURCES
  src/main.c
  src/utils.c
)

set(HEADERS
  src/utils.h
  src/player.h
)

# Skip pkg-config and directly set paths for raylib-tileson
# These paths will be set from environment variables in the nix-shell
set(RAYLIB_TILESON_INCLUDE_DIR "$ENV{RAYLIB_TILESON_INCLUDE}")
set(RAYLIB_TILESON_LIB_DIR "$ENV{RAYLIB_TILESON_LIB}")

# Check that paths are set
if(NOT RAYLIB_TILESON_INCLUDE_DIR)
  message(FATAL_ERROR "RAYLIB_TILESON_INCLUDE environment variable not set")
endif()
if(NOT RAYLIB_TILESON_LIB_DIR)
  message(FATAL_ERROR "RAYLIB_TILESON_LIB environment variable not set")
endif()

message(STATUS "Using raylib-tileson include dir: ${RAYLIB_TILESON_INCLUDE_DIR}")
message(STATUS "Using raylib-tileson lib dir: ${RAYLIB_TILESON_LIB_DIR}")

# Check for raylib
find_package(raylib 5.5 QUIET)

if(NOT raylib_FOUND)
  include(FetchContent)
  set(FETCHCONTENT_QUIET FALSE)

  set(BUILD_EXAMPLES
      OFF
      CACHE BOOL "" FORCE)
  set(BUILD_SHARED_LIBS
      OFF
      CACHE BOOL "" FORCE)
  set(USE_MSVC_RUNTIME_LIBRARY_DLL
      ON
      CACHE BOOL "" FORCE)

  FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
    GIT_PROGRESS TRUE)

  FetchContent_MakeAvailable(raylib)
  set(RAYLIB_LIBRARY raylib)
else()
  set(RAYLIB_LIBRARY raylib)
endif()

if(WIN32)
  set(PLATFORM_LIBS winmm opengl32 gdi32 glu32)
endif()

# Target
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${RAYLIB_TILESON_INCLUDE_DIR})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE stdc++)
target_link_libraries(${PROJECT_NAME} PRIVATE ${RAYLIB_LIBRARY})
target_link_libraries(${PROJECT_NAME} PRIVATE "${RAYLIB_TILESON_LIB_DIR}/libraylib-tileson.a")

if(WIN32)
  target_link_libraries(${PROJECT_NAME} PRIVATE ${PLATFORM_LIBS})
elseif(APPLE)
  target_link_libraries(
    ${PROJECT_NAME} PRIVATE "-framework IOKit" "-framework Cocoa"
                            "-framework OpenGL")
endif()
